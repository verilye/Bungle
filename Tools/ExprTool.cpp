#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


// generating code for all different permutations of the Expr class
// Because Im generating boilerplate, maybe dont bother seperating shit into 
// headers? Or only generate headers?

void defineType(std::ofstream & MyFile, std::string className, std::string fieldList) {

	MyFile << "  class " + className + ": public " + className + " {\n";

	// Constructor

	MyFile << "   " + className + "(" + fieldList + ")\n";

	// Parse string through the stream and seperate by delimiter
	std::istringstream stream(fieldList);
	std::string token; 
	vector<std::string> fields;

	while (getline(stream, token, ", ")) {
		fields.pushback(token);
	}
	// iterate through vector and print the fields out so its C++ code. 
	// using an iterator here to be a fancy lad

	vector<std::string>::iterator iter = fields.begin();

	MyFile << "\n:";
	for (iter; iter<fields.size(); iter++) {
		// Put the field names in the constructor after the parameter list
		// in c++ convention
		MyFile << *iter << "(" << *iter << "),";
	}
	MyFile << "{}\n";

	iter = fields.begin();
	// Declaring fields outside the constructor
	for (iter; iter < fields.size(); iter++) {
		MyFile << "    const " + *iter + ";\n";
	}

	MyFile << "}";
}


void defineAst( std::string outputDir, std::string baseName, List<std::string> types) {
	std::string path = outputDir + "/" + baseName + ".cpp";
	// write to file
	std::ofstream MyFile(path);
	// include the header
	MyFile << "#include \"Expr.h\" \n";
	MyFile << "#include <list> \n";
	MyFile << "\n class " + baseName + " {\n";

	// The AST classes.

	std::istringstream stream(fieldList);
	std::string token;
	vector<std::string> fields;

	while (getline(stream, token, ", ")) {
		fields.pushback(token);
	}

	vector<std::string>::iterator iter = fields.begin();
	for (iter; iter < fields.size(); iter++) {

		//TODO rejig this, its still half java bullshit
		std::string className = *iter[0];
		std::string fields = *iter[1];
		defineType(MyFile, baseName, className, fields);
	}
	
	MyFile << "}";
	MyFile.close();

}

int main(int argc, char * argv[]) {
	
	if (argc != 2) {
		std::cout << "Usage: generate_ast <output_directory>";
		return 64;
	}

	std::string outputDir = argv[0];
	defineAst(outputDir, "Expr", Arrays.asList(
		"Binary : Expr left, Token operatorToken, Expr right",
		"Grouping : Expr expression",
		"Literal : Object value",
		"Unary : Token operatorToken, Expr right"
	));

}