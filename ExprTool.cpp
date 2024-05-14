#include <iostream>
#include <list>
#include <string>
#include <fstream>


// generating code for all different permutations of the Expr class
// Because Im generating boilerplate, maybe dont bother seperating shit into 
// headers? Or only generate headers?

void defineAst( std::string outputDir, std::string baseName, List<std::string> types) {
	std::string path = outputDir + "/" + baseName + ".java";
	// write to file
	ofstream MyFile(path);
	// include the header
	MyFile << "#include \"Expr.h\" \n";
	MyFile << "#include <list> \n";
	MyFile << "\n class " + baseName + " {\n";
	
	MyFile << "}";


	MyFile.close();

}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		std::cout << "Usage: generate_ast <output_directory>";
		return 64;
	}

	std::string outputDir = args[0];
	defineAst(outputDir, "Expr", Arrays.asList(
		"Binary : Expr left, Token operatorToken, Expr right",
		"Grouping : Expr expression",
		"Literal : Object value",
		"Unary : Token operatorToken, Expr right"
	));

}