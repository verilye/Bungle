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
	}
}

void Bungle::run(std::string source) {

	// Break string into tokens and print them out on new lines every time
	// Create a java-list like structure and store the string in it using spaces as the delimiter ()
	// Im going to use a vector here, a cursory look online makes it seem like vectors are better for traversing
	// and linked lists are better for insertion only


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

	Scanner* scanner = new Scanner(source);
	std::vector<Token*> tokens = scanner->scanTokens();

	// Print tokens out using Token printer in Token class
	/*
	for (unsigned int i = 0; i <tokens.size(); i++) {
		tokens[i]->printToken();
	}
	*/
	
	Parser * parser = new Parser(tokens);
	Expr * expression = parser->parse();

	// Stop if there was a syntax error
	if(hadError) return;

	AstVisitor * printer = new AstVisitor();
	std::cout << printer->print(expression);
	

}
