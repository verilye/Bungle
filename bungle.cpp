#include <bungle.h>

int main(int argc, char* argv[]) {

	if (argc > 1) {
		std::cout << "(Usage: bungle [script])\n";
		return 64;
	}
	else if (argc == 1) {
		runFile(argv[0]);
	}
	else {
		runPrompt();
	}


	return 0;
}

private static void runFile(std::string path) {
	
	// Read all code from file and feed it into the run function
	// Open the file in binary mode
	std::ifstream infile(path, std::ios_base::binary);
	
	// Use istreambuf_iterator to read file into vector
	std::vector<char> buffer(std::istreambuf_iterator<char>(infile)),
							 std::istreambuf_iterator<char>());

	// Convert vector<char> into string using string constructor
	string str(buffer.begin(), buffer.end());

	return str;

}

private static void runPrompt() {

	// run code one line at a time like live python code
	std::string line = "";

	for (;;) {
		std::cout << "> ";
		std::getline(std::cin, input);
		if (line == null) {
			break;
		}
		run(line);
	}
}

private static void run(std::string source) {

	// Break string into tokens and print them out on new lines every time


}

