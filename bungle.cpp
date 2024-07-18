#include "bungle.h"

int main(int argc, char* argv[]) {
	Bungle* bungle = new Bungle();
	
	if (argc > 2) {
		std::cout << "(Usage: bungle [script])\n";
		return 64;
	}
	else if (argc == 2) {
		bungle->runFile(argv[1]);
	}
	else {
		bungle->runPrompt();
	}

	// check error reporting system for error flag
	if (hadError) {
		return 65;
	}

	if(hadRuntimeError){
		return 70;
	}

	// TEST AST PRINTER
	// AstVisitor* printer = new AstVisitor();
	// printer->TestMethod();

	return 0;
}

void Bungle::runFile(std::string path) {
	
	// Read all code from file and feed it into the run function
	// Open the file in binary mode
	std::ifstream infile(path, std::ios_base::binary);

	if (!infile.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}
	
	// Use istreambuf_iterator to read file into vector
	std::vector<char> buffer((std::istreambuf_iterator<char>(infile)),
							 std::istreambuf_iterator<char>());

	// Convert vector<char> into string using string constructor
	std::string str(buffer.begin(), buffer.end());

	run(str);

}

void Bungle::runPrompt() {

	// run code one line at a time like live python code
	std::string line = "";

	for (;;) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if (line.size()<=0) {
			break;
		}
		run(line);
		hadError = false;
		hadRuntimeError = false;
	}
}

void Bungle::run(std::string source) {

	// TEST CODE TO VISUALISE TOKENS
	//std::vector<std::string> vec;
	//if (!source.empty()) {
	//	int start = 0;

	//	do {
	//		// Find the delimiter
	//		int index = source.find(" ", start);
	//		if (index == std::string::npos) {
	//			break;
	//		}

	//		// If found, add the substring to the vector

	//		int length = index - start;
	//		vec.push_back(source.substr(start, length));
	//		start += (length + 1);

	//	} while (true);

	//	vec.push_back(source.substr(start,source.back()));
	//}

	Interpreter * interpreter = new Interpreter();
	Scanner* scanner = new Scanner(source);
	std::vector<Token*> tokens = scanner->scanTokens();

	// Print tokens out using Token printer in Token class
	/*
	for (unsigned int i = 0; i <tokens.size(); i++) {
		tokens[i]->printToken();
	}
	*/
	
	Parser * parser = new Parser(tokens);
	std::list<std::shared_ptr<Stmt>> statements = parser->parse();

	// Stop if there was a syntax error
	if(hadError) return;

	interpreter->interpret(statements);

	//Print the AST
	// AstVisitor * printer = new AstVisitor();
	// std::cout << printer->print(expression);

}
