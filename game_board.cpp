#include "stdafx.h"
#include "game_board.h"
#include "enumer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

int read_dimensions(std::ifstream & stream, unsigned int & a, unsigned int & b) {
	std::string line;
	bool t1, t2, t3;
	if (getline(stream, line)) {
		t1 = true;// getting ready for returning specific errors
	}
	std::istringstream iss(line);

	//iss >> a >> b;

	if (iss >> a) {
		t2 = true;
	}
	else {
		t2 = false;
	}
	if (iss >> b) {
		t3 = true;
	}
	else {
		t3 = false;
	}

	if (t1 && (!t2 || !t3)) {
		return  read_line_no_dimensions;
	}
	else if (!t1) {
		return no_line_read;
	}
	return success;

}

int read_game_pieces(std::ifstream & stream, std::vector<game_piece> & vect, unsigned int & width, unsigned int & height) {
	std::string line;
	std::string color, name, display;
	unsigned int x, y;
	bool sc = false;
	while (getline(stream, line)) {

		std::istringstream iss(line);
		iss >> color >> name >> display >> x >> y;
		// calling the method to turn the string into a type enum.
		game_pieces col = string_to_piece(color);
		//getting the dimensions of the board to compare to 


		//below are the conditions so that if they are not met we will skip that line and continue to the subsequent line
		if (col != invalid_color && x <= width && y <= height) { //then the proper conditions are met to continue
			int index = width * y + x;

			vect[index].piece = col;
			vect[index].piece_name = name;
			vect[index].piece_representation = display;
			sc = true; //setting the flag to true for 1 correct name piece
		}

	}
	// the last 2 sentences of #12 below
	if (sc) {
		return success;
	}
	else {
		return no_piece_read;
	}

}


void print_board(const std::vector<game_piece> & vect, unsigned int & width, unsigned int & height) {

	for (int y = height - 1;y >= 0;y--) {
		for (int x = 0;x < width;x++) {  //j>=0 ? *********
			int index = width * y + x;
			std::cout << vect[index].piece_representation;


		}
		std::cout << std::endl;
	}


}