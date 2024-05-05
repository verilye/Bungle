#ifndef BUNGLE_H
#define BUNGLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "scanner.h"
#include "error.h"

class Bungle {
	
public:
	static void runFile(std::string path);
	static void runPrompt();
private:
	
	static void run(std::string source);
};


#endif