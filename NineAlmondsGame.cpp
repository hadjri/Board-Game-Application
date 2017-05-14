#include "stdafx.h"
#include "NineAlmondsGame.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
NineAlmondsGame::NineAlmondsGame(unsigned int h, unsigned int w,
	game_pieces color, std::string name,
	std::string symbol) : GameBase(h, w, color, name, symbol, "", "") {
	vector<string> strings;
	string line;
	//initialize the board to 5x5. or whatever hxv is.
	height = h;
	width = w;

	ifstream ifs("NineAlmondsGame.txt");
	if (ifs.is_open()) {

		while (getline(ifs, line)) {
			strings.push_back(line);
		}
	}
	if (strings.size() == 0 || strings[1] == "NO DATA") {//allows the situation when no NineAlmondsGame.txt exists
		game_piece temp_piece_empty = {};
		temp_piece_empty.piece = no_color;
		temp_piece_empty.piece_name = "empty";
		temp_piece_empty.piece_representation = " ";

		game_piece temp_piece = {};
		temp_piece.piece = brown_almond;
		temp_piece.piece_name = "brown almond";
		temp_piece.piece_representation = "A";

		for (int y = height - 1;y >= 0;y--) {
			for (int x = 0;x < width;x++) {
				int index = width * y + x;
				//now conditions so that only inner 3 squares are fillled
				if (x != 0 && y != 0 && x != width - 1 && y != height - 1) {
					gameboard.push_back(temp_piece);
				}
				else {
					gameboard.push_back(temp_piece_empty);

				}



			}
			std::cout << std::endl;
		}
	
	
	}
	else {

		game_piece temp_piece_empty = {};
		temp_piece_empty.piece = no_color;
		temp_piece_empty.piece_name = "empty";
		temp_piece_empty.piece_representation = " ";

		for (int i = 0; i < h*w; ++i) {
			gameboard.push_back(temp_piece_empty);
		}

		for (int i = h; i >= 1; i--) {//3
			for (int j = 0; j < h; j++) {

				int index =h * (i - 1) + j;


				game_piece temp_piece = {};
				temp_piece.piece = brown_almond;
				temp_piece.piece_name = "Brown almond";
				if (strings[h + 1 - i].at(j) != 'e') {
					temp_piece.piece_representation = strings[h + 1 - i].at(j);
				}
				else {
					temp_piece = temp_piece_empty;

				}
				gameboard[index] = temp_piece;


			}
			cout << endl;
		}
		
	}
}


std::ostream &operator<< (std::ostream &out, const NineAlmondsGame &n)
{
	//to print out the board each time cout is called to the object.
	for (int y = n.height - 1;y >= 0;y--) {
		out << y;
		out << " ";
		for (int x = 0;x <n.width;x++) {  //j>=0 ? *********
			int index = n.width * y + x;
			out << n.gameboard[index].piece_representation + " ";


		}
		out << std::endl << std::endl;
	}
	out << "X 0 1 2 3 4" << std::endl;
	return out;

}

//method implementations from class

bool NineAlmondsGame::done() {

	int count_empty = 0;
	int status = 0; // The status flag, 0 means not true
	int size = width * height;


	for (int i = 0; i< size; ++i)
	{
		// check if there is a piece on the board not in the middle
		if (i != 12 && gameboard[i].piece == no_color)
		{
			++count_empty;
		}
		// check if there is a piece on the board in the middle
		if (i == 12 && gameboard[i].piece != no_color)
		{
			status = 1;
		}
	}
	if (status == 1 && count_empty == 24)
	{
		return true;
	}
	else
	{
		return false;
	}


	return false;
}

bool NineAlmondsGame::stalemate() {

	int w = width;
	// iterate the board to find pieces
	for (int h = height - 1; h + 1 != 0; --h)
	{
		for (int j = 0; j < width; ++j)
		{
			//check whether it is empty
			if (gameboard[w*h + j].piece != no_color)
			{
				//a few different cases to consider.
				//case #1
				if (h <= 2 && j >= 2)
				{
					if (gameboard[w*(h + 2) + (j - 2)].piece == no_color &&
						gameboard[w*(h + 1) + (j - 1)].piece != no_color
						)
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #2
				if (h <= 2)
				{
					if (gameboard[w*(h + 2) + j].piece == no_color &&
						gameboard[w*(h + 1) + j].piece != no_color
						)
					{
						return false;
					}
				}


				//case #3
				if ((h <= 2) && (j <= 2))
				{
					if (gameboard[w*(h + 2) + (j + 2)].piece == no_color &&
						gameboard[w*(h + 1) + (j + 1)].piece != no_color
						)
					{
						return false;
					}
				}


				//case #4
				if (j >= 2)
				{
					if (gameboard[w*h + (j - 2)].piece == no_color &&
						gameboard[w*h + (j - 1)].piece != no_color
						)
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #d
				if (j <= 2)
				{
					if (gameboard[w*h + (j + 2)].piece == no_color &&
						gameboard[w*h + (j + 1)].piece != no_color
						)
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #6
				if (j >= 2 && h >= 2)
				{
					if (gameboard[w*(h - 2) + (j - 2)].piece == no_color &&
						gameboard[w*(h - 1) + (j - 1)].piece != no_color
						)
					{
						return false;
					}
				}

				//case #7
				if (h >= 2)
				{
					if (gameboard[w*(h - 2) + j].piece == no_color &&
						gameboard[w*(h - 1) + j].piece != no_color
						)
					{
						return false;
					}
				}

				// a move may have 8 directions
				//case #8
				if (h >= 2 && j <= 2)
				{
					if (gameboard[w*(h - 2) + (j + 2)].piece == no_color &&
						gameboard[w*(h - 1) + (j + 2)].piece != no_color
						)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}


int NineAlmondsGame::turn() {
	unsigned int a, b, x, y;//might have to init them
	int count = 0;
	bool continue_turn = true;



	while (count != 2) {
		if (prompt(a, b) == user_quit) {
			
			std::cout << "Quit turn." << endl;
			return user_quit;
		}
		else { //success
			while (gameboard[width*b + a].piece == no_color) {//must be an empty  spave //is it width*b + a? --cw
				std::cout << "(" << a << "," << b << ") is an empty space. please select a coordinate with an almond." << endl;
				if (prompt(a, b) == user_quit) {
					return user_quit;
				}
			}
			count++;
		}
		if (prompt(x, y) == user_quit) {
			std::cout << "Quit turn." << endl;
			return user_quit;
		}
		else {//must be an empty space
			while (gameboard[width*y + x].piece != no_color) {//must be a filled spave
				std::cout << "(" << x << "," << y << ") is a filled space. please select a coordinatethat is empty." << endl;
				if (prompt(x, y) == user_quit) {
					return user_quit;
				}
			}

			//so first we will check tha middle point between a,b and x,y is filled. then check that the move is within 2 in all directions
			//midpoint check below
			int square = (a - x) * //distance formula for the 2 points to check that it is in teh radius
				(a - x) +
				(b - y) *
				(b - y);
			//calculate the module
			int	modx = (a + x) % 2;
			int	mody = (b + y) % 2;


			int midax = (a + x) / 2;
			int middleby = (b + y) / 2;
			while (gameboard[width*middleby + midax].piece == no_color) {
				std::cout << "the middle position must be filled with an almond. please reenter second coordinates." << endl;
				if (prompt(x, y) == user_quit) {
					return user_quit;
				}
			}
			while (!((square <= 8) && (modx == 0) && (mody == 0))) {
				std::cout << "your second coordinate is not within 2 spaces of the previous one. please re-enter a second coordinate." << endl;
				if (prompt(x, y) == user_quit) {
					return user_quit;
				}

				//have to rerun the numbers to check.
				square = (a - x) * //distance formula for the 2 points to check that it is in teh radius
					(a - x) +
					(b - y) *
					(b - y);
				//calculate the module
				modx = (a + x) % 2;
				mody = (b + y) % 2;



			}
			count++;
		}

	}
	//then we have a valid move and can continue.
	std::cout << "VALID MOVE";
	std::cout << "(" << a << "," << b << ") to (" << x << "," << y << ")" << endl;
	//now we will remove the middle almond and print out the new screen.

	game_piece temp_piece_empty = {};
	temp_piece_empty.piece = no_color;
	temp_piece_empty.piece_name = " ";
	temp_piece_empty.piece_representation = " ";

	game_piece temp_piece = {};
	temp_piece.piece = brown_almond;
	temp_piece.piece_name = "A";
	temp_piece.piece_representation = "A";

	//make the middle almond dissapear
	gameboard[width*((b + y) / 2) + ((a + x) / 2)] = temp_piece_empty;
	//and make the original almond appear in new spot.
	gameboard[width*b + a] = temp_piece_empty;
	gameboard[width*y + x] = temp_piece;



	//print the board
	std::cout << *this; //print out board by dereferencing the object called in main.
	std::cout << endl;
	while (continue_turn) {
		std::cout << "Continue this turn (y/n)?" << endl;
		char con;
		cin >> con;
		if (con == 'y') {
			continue_turn = true;

			//redo all the same checks but for the new values

			unsigned int newx = 0;
			unsigned int	 newy = 0;


			if (prompt(newx, newy) == user_quit) {
				std::cout << "Quit turn." << endl;
				return user_quit;
			}
			else {//must be an empty space
				while (gameboard[width*newy + newx].piece != no_color) {//must be an open space
					std::cout << "(" << newx << "," << newy << ") is a filled space. please select a coordinatethat is empty." << endl;
					if (prompt(newx, newy) == user_quit) {
						return user_quit;
					}
				}

				//so first we will check tha middle point between a,b and x,y is filled. then check that the move is within 2 in all directions
				//midpoint check below
				int square = (x - newx) * //distance formula for the 2 points to check that it is in teh radius
					(x - newx) +
					(y - newy) *
					(y - newy);
				//calculate the module
				int	modx = (x + newx) % 2;
				int	mody = (y + newy) % 2;


				int midax = (x + newx) / 2;
				int middleby = (y + newy) / 2;
				while (gameboard[width*middleby + midax].piece == no_color) {
					std::cout << "the middle position must be filled with an almond. please reenter second coordinates." << endl;
					if (prompt(newx, newy) == user_quit) {
						return user_quit;
					}
				}
				while (!((square <= 8) && (modx == 0) && (mody == 0))) {
					std::cout << "your second coordinate is not within 2 spaces of the previous one. please re-enter a second coordinate." << endl;
					if (prompt(newx, newy) == user_quit) {
						return user_quit;
					}
				}

			}

			//make the middle almond dissapear
			gameboard[width*((y + newy) / 2) + ((x + newx) / 2)] = temp_piece_empty;
			//and make the original almond appear in new spot.
			gameboard[width*y + x] = temp_piece_empty;
			gameboard[width*newy + newx] = temp_piece;



			std::cout << *this;

			//reset so 'newx/y' are old ones
			x = newx;
			y = newy;

		}
		else if (con == 'n') {
			continue_turn = false;
			cout << "turn over";
			return turn_over;
		}
		else {
			cout << "INVALID INPUT";
			return bad_input;
		}

	}

	return turn_over;
}

void NineAlmondsGame::print() {
	std::cout << endl << *this << endl;
}


