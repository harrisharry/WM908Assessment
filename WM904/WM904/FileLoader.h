#pragma once
#include <iostream>
#include <string>
#include <FStream>
static class Loader {

public:
	bool LoadFile(std::string fileName) {
		
		std::ifstream infile(fileName);
		if (infile.is_open()) {
			std::cout << "Failed to open file, because it is already open.\n";
			return false;
		}

		std::string line;

		while (std::getline(infile,line)) {


			

		}

	}

};