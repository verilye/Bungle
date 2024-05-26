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

	MyFile << "  class " + className + ": public Expr {\n";

	// Parse string through the stream and seperate by delimiter
	std::istringstream stream(fieldList);
	std::string token;
	std::vector<std::string> fields;

	while (std::getline(stream, token, ','))
	{
		fields.push_back(token);
	}

	// Declaring fields outside the constructor
	for (const std::string& token : fields) {
		std::istringstream stream(token);
		std::string variableName;
		std::getline(stream, variableName);
		MyFile << "    const " + token + ";\n";		  
	}

	// Constructor
	MyFile << "   " + className + "(" + fieldList + ")\n";

	
	// iterate through vector and print the fields out so its C++ code. 
	// using an iterator here to be a fancy lad

	MyFile << "\n:";

		// Put the field names in the constructor after the parameter list
		// in c++ convention
		// Trim each token so that the variable type is not included in the declaration

	for (const std::string& token : fields) {
		std::istringstream stream(token);
		std::string variableName;
		std::getline(stream, variableName, ' ');
		std::getline(stream, variableName, ' ');
		std::getline(stream, variableName);

		MyFile << variableName << "(" << variableName << "),";
	}
	MyFile << "{}\n";

	MyFile << "};\n";

}

void defineVisitor(std::ofstream& MyFile, std::string baseName, std::list<std::string> types) {
	
	// In the example this only generates a single 'interface' which will be inherited from in
	// the defineAstfunction

	// REMEMBER - in C++, interface and abstract types do not exist like in C#
	// An abstract class is something that can be instatiated and inherited from
	// An interface would be something that has a pure virtual function in it
	//		so something that needs to be inherited from and filled out before it
	//		can be instantiated

	MyFile << "\n";
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
	MyFile << "#include \"Expr.h\" \n";
	MyFile << "#include \"Token.h\" \n";
	MyFile << "#include <list> \n";


	// Each kind of expression needs to act differently at runtime, but using a 
	// massive switch statement is bad for performance so we need to use a 
	// design pattern to handle it, the visitor pattern is suggested.

	// Adds a functional style paradigm to an object oriented language
	// as explained in Crafting Interpreters page 69.

	// Define visitor base class
	MyFile << "class ExprVisitor { \n";
	
	// in the example its basically an abstract java class with an interface inside
	defineVisitor(MyFile, baseName, types);


	MyFile << "}\n";
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

		defineType(MyFile,baseName, className, fields);
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

	std::list<std::string> astTypes{
		"Binary : Expr left, Token operatorToken, Expr right",
		"Grouping : Expr expression",
		"Literal : strliteral value",
		"Unary : Token operatorToken, Expr right"
	};

	std::string outputDir = argv[1];
	defineAst(outputDir, "ExprGen", astTypes);

}