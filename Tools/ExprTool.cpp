#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// Personal NOTE on C++ templates - All of my classes here are template classes
// this is why we are inheriting from Class<T> instead of just Class

void defineType(std::ofstream & MyFile, std::string baseName, std::string className, std::string fieldList) {
	
	MyFile << "class " + className + ": public Expr {\n";
	MyFile << "public:\n";

	// Parse string through the stream and separate by delimiter
	std::istringstream stream(fieldList);
	std::string token;
	std::vector<std::string> fields;

	while (std::getline(stream, token, ','))
	{
		fields.push_back(token);
	}

	// NOTE - C++ does not have virtual variables, only functions

	// Declaring fields outside the constructor
	for (const std::string& token : fields) {
		std::istringstream stream(token);
		std::string variableName;
		std::getline(stream, variableName);
		MyFile << "	" + token + ";\n";		  
	}

	// Constructor
	MyFile << "	" + className + "(" + fieldList + ")\n";
	MyFile << "		:";

	// Put the field names in the constructor after the parameter list in c++ convention
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

	// Return built string from the ASTPrinterHelper class
	MyFile << "	virtual std::string accept(ExprVisitor& visitor) const override {\n";
	MyFile << "		return visitor.visit"+className.substr(0,className.length() - 1) + "ExprGen(*this);\n";
	MyFile << "	};\n";

	MyFile << "};\n\n";

}

void defineVisitor(std::ofstream& MyFile, std::string baseName, std::list<std::string> types) {

	// Define visitor base class
	MyFile << "class ExprVisitor { \n";
	MyFile << "public:\n";

	// Create methods to 'visit' all of the generated classes 
	for (const std::string& type : types) {
		std::istringstream stream(type);
		std::string typeName;
		std::getline(stream, typeName, ' ');

		MyFile << "	virtual std::string visit"+ typeName + baseName + "(const "+ typeName +"& ";
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

		MyFile << "class " << type << ";\n";
	}
	MyFile << "\n";
}

void defineBaseExpr(std::ofstream& MyFile) {

	MyFile << "class Expr { \n";
	MyFile << "public:\n";
	MyFile << "	virtual ~Expr() = default; \n"; 
	// This should be a pure virtual function
	MyFile << "	virtual std::string accept(ExprVisitor& visitor) const = 0; \n";

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

	// Forward declare classNames for visitor class
	forwardDeclare(MyFile, baseName, types); 

	// Visitor pattern used to identify type rather than massive switchstatement
	defineVisitor(MyFile, baseName, types);

	// Base Class for Subclasses to inherit from
	defineBaseExpr(MyFile);

	// Go through each list item and read className and types into seperate variables
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

	// Subclasses listed here in this format TO BE GENERATED 
	std::list<std::string> astTypes{
		"Binary : const Expr& left, const Token& operatorToken, const Expr& right",
		"Grouping : const Expr& expression",
		"Literal : const std::string& value",
		"Unary : const Token& operatorToken, const Expr& right"
	};

	std::string outputDir = argv[1];
	defineAst(outputDir, "ExprGen", astTypes);

}