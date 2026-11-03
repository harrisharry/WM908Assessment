#pragma once
#include <iostream>
#include <string>
#include <fstream>
static class Loader {

public:
	static bool LoadFile(std::string fileName) {
		
		std::ifstream inFile(fileName);
		if (!inFile.is_open()) {
			std::cout << "Failed to open file, because it is already open.\n";
			return false;
		}

		std::string line;

		while (std::getline(inFile,line)) {

			
			std::cout << line << "\n";
			

		}

		inFile.close();

		return true;
	}

};