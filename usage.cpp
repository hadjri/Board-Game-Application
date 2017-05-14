#pragma once



#pragma once

#include "stdafx.h"
#include "usage.h"
#include "enumer.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
using std::vector;

int usage_message(char* name, int x) {// as specified

	if (x == wrong_number_of_commands) { // first case -> wrong number of commands
										 //use the parameters of this function for your cout message rather than hard-coding the entore message - SB
		std::cout << "Only the name of the program, followed by \'NineAlmonds\' is necessary. is necessary. wrong number of commands." << std::endl;

		status failure = wrong_number_of_commands;
		return failure;
	}
	if (x == failure_file_not_found) { //case 2-> could not open file
		status failure = failure_file_not_found;
		std::cout << "Failure. File not found." << std::endl;
		return failure;
	}
	return success;
}

std::string to_Lower(std::string x) {
	std::transform(x.begin(), x.end(), x.begin(), ::tolower);
	return x;
}





int parse_file(vector<std::string>& vect, char* name) {
	std::ifstream finput;
	finput.open(name);// here we are declaring our input stream and 
					  //opening it according to the file name given as the second parameter
	std::string current_word;

	if (!finput.is_open()) {  // JAS: changed to is_open() here
		return usage_message("lab0", 2); // don't hardcode project name here, use argv[0].  Also, use enumerated status codes as well
										 // for example:   should be something like:  return usage_message(argv[0], failure_file_not_found);
	}

	while (finput >> current_word)
	{
		vect.push_back(current_word);
		//cout << current_word << endl;//test
	}


	return success; //0 indicates success.
}