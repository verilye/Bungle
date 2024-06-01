#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// generating code for all different permutations of the Expr class
// Because Im generating boilerplate, maybe dont bother seperating shit into 
// headers? Or only generate headers?

void defineType(std::ofstream & MyFile, std::string baseName, std::string className, std::string fieldList) {
	
	
	MyFile << "template <typename T>\n";
	MyFile << "class " + className + ": public Expr<T> {\n";

	// Parse string through the stream and seperate by delimiter
	std::istringstream stream(fieldList);
	std::string token;
	std::vector<std::string> fields;

	while (std::getline(stream, token, ','))
	{
		fields.push_back(token);
	}

	// NOTE -- Why are we redeclaring fields in a subclass declaration
	// C++ does not have virtual variables, only functions

	// It seems that variables should be declared in each of the subclasses instead
	// of the super class, this could be wrong but Im going to go with that for now

	// Declaring fields outside the constructor
	for (const std::string& token : fields) {
		std::istringstream stream(token);
		std::string variableName;
		std::getline(stream, variableName);
		MyFile << "	" + token + ";\n";		  
	}

	// Constructor
	MyFile << "	" + className + "(" + fieldList + ")\n";

	
	// iterate through vector and print the fields out so its C++ code. 
	// using an iterator here to be a fancy lad
	MyFile << "		:";

	// Put the field names in the constructor after the parameter list
	// in c++ convention
	// Trim each token so that the variable type is not included in the declaration

	for (const std::string& token : fields) {
		std::istringstream stream(token);
		std::string variableName;
		std::getline(stream, variableName, ' ');
		std::getline(stream, variableName, ' ');
		std::getline(stream, variableName, ' ');
		std::getline(stream, variableName);

		MyFile << variableName << "(" << variableName << ")";

		if (token != fields.back()) {
			MyFile << ",";
		}
	}
	MyFile << "{}\n\n";

	MyFile << "	virtual T accept(ExprVisitor<T> visitor) override {\n";
	MyFile << "		return visitor.visit(*this);\n";
	MyFile << "	};\n";

	MyFile << "};\n\n";

}

void defineVisitor(std::ofstream& MyFile, std::string baseName, std::list<std::string> types) {

	// Define visitor base class
	MyFile << "template <typename T>\n";
	MyFile << "class ExprVisitor { \n";

	// Create methods to 'visit' all of the generated classes 
	for (const std::string& type : types) {
		std::istringstream stream(type);
		std::string typeName;
		std::getline(stream, typeName, ' ');
		MyFile << "	virtual T visit"+ typeName + baseName + "("+ typeName + "<T>& ";
		MyFile << "expression) = 0;\n";
	}

	MyFile << "};\n\n";
	
}

void forwardDeclare(std::ofstream& MyFile, std::string baseName, std::list<std::string> types) {

	// Forward declare type classes
	for (const std::string& typeName : types) {
		std::istringstream stream(typeName);
		std::string type;
		std::getline(stream, type, ' ');

		MyFile << "template <typename T> class " << type << ";\n";
	}
	MyFile << "\n";
}

void defineBaseExpr(std::ofstream& MyFile) {

	MyFile << "template <typename T>\n";
	MyFile << "class Expr { \n";

	// All subclassess have different fields, doesnt make sense to declare them in the parent class
	/*MyFile << "	const Expr<T> left; \n";
	MyFile << "	const Token operatorToken; \n";
	MyFile << "	const Expr<T> right; \n";*/

	MyFile << "	virtual ~Expr() = default; \n"; 
	// This should be a pure virtual function
	MyFile << "	virtual const T accept(ExprVisitor<T> visitor) const = 0; \n";

	MyFile << "};\n\n";
}

void defineAst(std::string outputDir, std::string baseName, std::list<std::string> types) {
	
	std::string path = outputDir + "/" + baseName + ".h";
	// write to file
	std::ofstream MyFile(path);
	if (!MyFile.is_open()) {
		std::cerr << "Failed to open file" << path << std::endl;
		return;
	}

	MyFile << "#ifndef EXPRGEN_H\n";
	MyFile << "#define EXPRGEN_H\n";

	// include the header
	MyFile << "#include \"Token.h\" \n";
	MyFile << "#include <list> \n";
	MyFile << "#include <string> \n";
	MyFile << "\n";

	// TODO

	// VIRTUAL NEEDS TO BE ADDED TO ALL INHERITED VALUES OF SUBCLASSES 

	// Forward declare classNames for visitor class
	forwardDeclare(MyFile, baseName, types); 

	// Visitor pattern used to identify type rather than massive switch
	// statement
	defineVisitor(MyFile, baseName, types);

	// Base Class for subs to inherit from
	defineBaseExpr(MyFile);

	// Go through each list item and read className and types into seperate variables
	// className is added onto the baseName which indicates it was generated code
	// Send fields through to be printed out in the defineTypes function

	for(const std::string &type : types){ 

		std::istringstream stream(type); 
		std::string className; 
		std::getline(stream, className, ':'); 
		std::string fields; 
		std::getline(stream, fields); 

		fields.erase(0, fields.find_first_not_of(' ')); 
		fields.erase(fields.find_last_not_of(' ') + 1); 

		defineType(MyFile, baseName, className, fields);
		// define accept functions in each of the subclasses to be visited by the visitor class

	}
	
	MyFile << "#endif";
	MyFile.close();

}

int main(int argc, char * argv[]) {
	
	if (argc != 2) {
		std::cout << "Usage: generate_ast <output_directory>";
		return 64;
	}

	// Subclasses listed here
	std::list<std::string> astTypes{
		"Binary : const Expr<T>& left, const Token& operatorToken, const Expr<T>& right",
		"Grouping : const Expr<T>& expression",
		"Literal : const std::string& value",
		"Unary : const Token& operatorToken, const Expr<T>& right"
	};

	std::string outputDir = argv[1];
	defineAst(outputDir, "ExprGen", astTypes);

}