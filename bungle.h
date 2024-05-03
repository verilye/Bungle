#ifndef BUNGLE_H
#define BUNGLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


class Bungle {
	
public:
	static bool hadError;
	static void error(int line, std::string message);
	static void runFile(std::string path);
	static void runPrompt();
	
private:
	
	static void run(std::string source);
	static void report(int line, std::string where, std::string message);
};

bool Bungle::hadError = false;

#endif