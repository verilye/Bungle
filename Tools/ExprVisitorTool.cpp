#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


void defineVisitor(std::ofstream& MyFile, std::string baseName, std::list<std::string> types) {
	// Create methods to 'visit' all of the generated classes 
	for (const std::string& type : types) {
		MyFile << "	virtual std::string visit"+ type + baseName + "(const "+ type +"* ";
		MyFile << "expression) = 0;\n";
	}
	
}

int main(int argc, char * argv[]){

    if (argc != 2) {
		std::cout << "Usage: generate_exprVisitor <output_directory>";
		return 64;
	}

    std::string path = (std::string)argv[1] + "/ExprVisitorGen.h";
    std::ofstream MyFile(path);
    if (!MyFile.is_open()) {
		std::cerr << "Failed to open file" << path << std::endl;
		return -1;
	}

    MyFile << "#ifndef EXPRVISITORGEN_H\n";
	MyFile << "#define EXPRVISITORGEN_H\n";

	// include the header
	MyFile << "#include \"../token.h\" \n";
	MyFile << "#include <list> \n";
	MyFile << "#include <string> \n";
	MyFile << "\n";
    MyFile <<"class Binary;\n";
    MyFile <<"class Grouping;\n";
    MyFile <<"class Literal;\n";
    MyFile <<"class Unary;\n";
    MyFile <<"class ExpressionStmt;\n";
    MyFile <<"class PrintStmt;\n";
    MyFile <<"class VarStmt;\n";
    MyFile <<"class Variable;\n";

    std::list<std::string> exprTypes{
        "Binary",
        "Grouping", 
        "Literal",
        "Unary",
        "Variable",
    };

    std::list<std::string> stmtTypes{
        "ExpressionStmt",
        "PrintStmt",
        "VarStmt"
    };

    // Define visitor base class
	MyFile << "class ExprVisitor { \n";
    MyFile << "public:\n";

    // Generate visitor pattern for all Expr subclasses
	defineVisitor(MyFile, "ExprGen", exprTypes);
    // Generator visitor pattern for Stmt subclasses
    defineVisitor(MyFile, "Gen", stmtTypes);

    MyFile << "};\n\n";

    MyFile << "#endif";
	MyFile.close();
    

}