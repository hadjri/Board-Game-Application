#include "stdafx.h"
#include "ReversiGame.h"
#include "game_board.h"
#include "stdafx.h"
#include "ReversiGame.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

ReversiGame::ReversiGame(unsigned int h,unsigned int v, game_pieces color, std::string name, std::string symbol, string p1, string p2):GameBase(h, v, color, name, symbol,p1,p2),player1(p1),player2(p2) {
	whoseturn = player1;
	game_piece temp_piece_empty = {};
	temp_piece_empty.piece = no_color;
	temp_piece_empty.piece_name = "empty";
	temp_piece_empty.piece_representation = " ";
	
	for (int i = 0;i < h*v; ++i) {
		gameboard.push_back(temp_piece_empty);
	}
	
	vector<string> strings;
	string line;
	ifstream ifs("ReversiGame.txt");
	if (ifs.is_open()) {

		while (getline(ifs, line)) {
			strings.push_back(line);
		}
	}
		if (strings.size() == 0 || strings[1] == "NO DATA") {//allows the situation when no ReversiGame.txt exists

			game_piece temp_piece_white = {};
			temp_piece_white.piece = o_reversi;
			temp_piece_white.piece_name = "white";
			temp_piece_white.piece_representation = "O";

			game_piece temp_piece_black = {};
			temp_piece_black.piece = x_reversi;
			temp_piece_black.piece_name = "black";
			temp_piece_black.piece_representation = "X";

			//initialize game from start.

			gameboard[8 * 3 + 4] = temp_piece_white;
			gameboard[8 * 4 + 3] = temp_piece_white;
			gameboard[8 * 3 + 3] = temp_piece_black;
			gameboard[8 * 4 + 4] = temp_piece_black;
		}
		else {

			game_piece temp_piece_empty = {};
			temp_piece_empty.piece = no_color;
			temp_piece_empty.piece_name = "empty";
			temp_piece_empty.piece_representation = " ";


			for (int i = 0; i < h*v; ++i) {
				gameboard.push_back(temp_piece_empty);
			}

			for (int i = v; i >= 1; i--) {//3
				for (int j = 0; j < v; j++) {

					int index = v * (i - 1) + j;


					game_piece temp_piece = {};
					temp_piece.piece = reversi;
					temp_piece.piece_name = "Reversi Piece";
					if (strings[v + 1 - i].at(j) != 'e') {
						temp_piece.piece_representation = strings[v + 1 - i].at(j);
					}
					else if (strings[v + 1 - i].at(j) == 'O') {
						temp_piece.piece_representation = "O";
						temp_piece.piece = white;

					}
					else if (strings[v + 1 - i].at(j) == 'X') {
						temp_piece.piece_representation = "X";
						temp_piece.piece = black;

					}
					else {
						temp_piece.piece_representation = " ";
						temp_piece.piece = no_color;
					}
					gameboard[index] = temp_piece;
				}
				cout << endl;
			}



			whoseturn = strings[strings.size() - 1];
		}
	}




bool ReversiGame::done()
{
	bool a = false;
	bool b = no_moves();
	

	bool greater_exists = false;

	for (int i = 0;i < gameboard.size(); ++i) {
		if (gameboard[i].piece_representation == " ") {
			a = false;
		}
		else {
			a = true;
		}
	}

	for (int i = 0;i < gameboard.size(); ++i) {
		if (gameboard[i].piece_representation == "X") {
			count_x++;
		}
		else if(gameboard[i].piece_representation == "O") {
			count_o++;
		}
	}

	bool c = false;

	if (a || b) {
		
		c = true;
		
	}

	if (count_x > count_o || count_o > count_x) {
		greater_exists = true;
	}



	if (greater_exists && c) {
		return true;
	}

	
	return false;
}

bool ReversiGame::no_moves()
{
	bool a = w_available_square();
	bool b = b_available_square();
	if (!a && !b) {
		return true;
	}
	else {
		return false;
	}
}

bool ReversiGame::stalemate()
{
	bool a = false; //filled board
	bool b = no_moves(); //no moves remaining
	bool c = false; //a or b

	for (int i = 0;i < gameboard.size(); ++i) {
		if (gameboard[i].piece_representation == " ") {
			a = false;
			break;
		}
		else {
			a = true;
		}
	}


	if (a || b) { //if board is full or if no moves is TRUE
		c = true;
	}
	bool x = (count_o == count_x);

	if (c && count_o == count_x) { //if c and equal pieces
		cout << x << endl;
		cout << count_o << " " << count_x;
		return true;
	}


	return false;
}

void ReversiGame::print()
{
	std::cout << endl << *this << endl;
}


;
int ReversiGame::turn()
{

	unsigned int p1x = 0;// the position of the first_person selected piec
	unsigned int p1y = 0;// the position of the first_person selected piece
	unsigned int p2x = 0;// the position of the second_person selected piece
	unsigned int p2y = 0;// the position of the second_person selected piece
	int valid_move = 1; // 0 means valid, 1 means invalid
						 // if it is the first person's (X) turn

	if (whoseturn == player1)

	{

		// if p1 has a valid square

		if (b_available_square() == true)

		{

			cout << player1 << "'s turn, use X pieces.  Select valid coordinates, or quit." << endl;

			valid_move = prompt(p1x, p1y);
			
			if (valid_move == user_quit) {
			
				return user_quit;
			}
			
			while ((valid_move != success) || (gameboard[width*p1y + p1x].piece_representation != " ") ||available_move_black(p1x, p1y) != true){

				if (valid_move != success){

					cout << "Bad command" << endl;

					valid_move = prompt(p1x, p1y);

				}

				else if (gameboard[width*p1y + p1x].piece_representation != " ")
					 
				{
					cout << "There is already a piece there." << endl;

					valid_move = prompt(p1x, p1y);
					if (valid_move == user_quit) {

						return user_quit;
					}
				}

				else

				{

					cout << "Invalid position input." << endl;

					valid_move = prompt(p1x, p1y);
					if (valid_move == user_quit) {

						return user_quit;
					}
				}

			}

			black_done(p1x, p1y);

			print();

			whoseturn = player2;

		}

		else

		{

			// change turn

			whoseturn = player2;

			cout << player1 << "'s turn has been skipped due to lack of valid squares." << endl;

		}

	}

	else if (whoseturn == player2)

	{

		if (w_available_square() == true)

		{

			cout << player2 << "'s turn, use O pieces.  Select valid coordinates, or quit." << endl;

			valid_move = prompt(p2x, p2y);
			if (valid_move == user_quit) {

				return user_quit;
			}

			while ((valid_move != success) || (gameboard[width*p2y + p2x].piece != no_color) || available_move_white(p2x, p2y) != true)	{

				if (valid_move != success)

				{

					cout << "Bad command." << endl;

					valid_move = prompt(p2x, p2y);
					if (valid_move == user_quit) {

						return user_quit;
					}

				}

				else if (gameboard[width*p2y + p2x].piece != no_color)

				{

					cout << "There is already a piece there." << endl;

					valid_move = prompt(p2x, p2y);
					if (valid_move == user_quit) {

						return user_quit;
					}
				}

				else

				{

					cout << "Invalid position input." << endl;

					valid_move = prompt(p2x, p2y);
					if (valid_move == user_quit) {

						return user_quit;
					}
				}

			}

			white_done(p2x, p2y);


			print();
			whoseturn = player1;

		}
		else

		{
			whoseturn = player1;
			cout << player2 << "'s turn skipped." << endl;
		}

	}
	return 0;
}




bool ReversiGame::w_available_square()
{
	unsigned int d = width;

	for (unsigned int i = height - 1; i + 1 != 0; --i) {

		for (unsigned int j = 0; j < width; ++j) {


			if (gameboard[d*i + j].piece == no_color) {

				if (available_move_white(j, i) == true) {

					return true;

				}
			}
		}
	}

	return false;

}

bool ReversiGame::b_available_square()
{
unsigned int d = width;

for(unsigned int i = height-1; i+1 != 0; --i ){

	for(unsigned int j = 0; j < width; ++j){


		if (gameboard[d*i+j].piece == no_color){

			if(available_move_black(j,i) == true){

				return true;

			}
		}
	}
}	

return false;

}


void ReversiGame::black_done(unsigned int i, unsigned int j) {

	game_piece temp_black = {};
	temp_black.piece = black;
	temp_black.piece_name = "black reversi";
	temp_black.piece_representation = "X";

	int x = 0; 
	int y = 0; 
	int n = 0; 
	gameboard[width*j + i] = temp_black;


	if (i >= 1 && j <= 6)

	{
		x = i - 1;
		y = j + 1;

		if (gameboard[width*y + x].piece_representation == "O") {

			--x;

			++y;

			while (x >= 0 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = y - j - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y - 1) + (x + 1)] = temp_black;

						--y;

						++x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				++y;

			}

		}

	}
	if (j <= 6)

	{

		x = i;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++y;

			while (y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = y - j - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y - 1) + x] = temp_black;
						--y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++y;

			}

		}

	}
	if (i <= 6 && j <= 6)

	{

		x = i + 1;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++x;

			++y;

			while (x <= 7 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = y - j - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y - 1) + (x - 1)] = temp_black;

						--y;

						--x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				++y;

			}

		}

	}
	if (i <= 6)

	{

		x = i + 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++x;

			while (x <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = x - i - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*y + (x - 1)] = temp_black;

						--x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;
			}
		}
	}
	if (i <= 6 && j >= 1)

	{

		x = i + 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++x;

			--y;

			while (x <= 7 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = x - i - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y + 1) + (x - 1)] = temp_black;

						--x;

						++y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				--y;

			}
		}
	}

	if (j >= 1)

	{

		x = i;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{

			--y;

			while (y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = j - y - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y + 1) + x] = temp_black;

						++y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--y;

			}

		}

	}

	if (i >= 1 && j >= 1)

	{

		x = i - 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			--x;

			--y;

			while (x >= 0 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = j - y - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y + 1) + (x + 1)] = temp_black;

						++x;

						++y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				--y;

			}

		}

	}

	if (i >= 1)

	{

		x = i - 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			--x;

			while (x >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{
					n = i - x - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*y + (x + 1)] = temp_black;

						++x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

			}

		}

	}
}

bool ReversiGame::available_move_black(unsigned int i, unsigned int j)
{
	

	int x = 0; 
	int y = 0; 

	if (i >= 1 && j <= 6)

	{

		x = i - 1;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			--x;

			++y;

			while (x >= 0 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				++y;

			}

		}

	}

	if (j <= 6)

	{

		x = i;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++y;

			while (y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++y;

			}

		}

	}
	if (i <= 6 && j <= 6)

	{

		x = i + 1;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++x;

			++y;

			while (x <= 7 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				++y;

			}

		}

	}
	if (i <= 6)

	{

		x = i + 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++x;

			while (x <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

			}

		}

	}
	if (i <= 6 && j >= 1)

	{

		x = i + 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			++x;

			--y;

			while (x <= 7 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X"){

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				--y;

			}

		}

	}

	if (j >= 1)

	{

		x = i;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{


			--y;

			while (y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--y;

			}

		}

	}

	if (i >= 1 && j >= 1)

	{

		x = i - 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			--x;

			--y;

			while (x >= 0 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				--y;

			}

		}

	}

	if (i >= 1)

	{

		x = i - 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "O")

		{
			--x;

			while (x >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "X")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

			}

		}

	}
	return false;

}

bool ReversiGame::available_move_white(unsigned int i, unsigned int j)
{
	int x = 0;
	int y = 0; 

	if (i >= 1 && j <= 6)

	{

		x = i - 1;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			--x;

			++y;

			while (x >= 0 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				++y;

			}

		}

	}

	if (j <= 6)

	{

		x = i;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++y;

			while (y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++y;

			}

		}

	}

	if (i <= 6 && j <= 6)

	{

		x = i + 1;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++x;

			++y;

			while (x <= 7 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				++y;

			}

		}

	}

	if (i <= 6)

	{

		x = i + 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++x;

			while (x <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

			}

		}

	}
	if (i <= 6 && j >= 1)

	{

		x = i + 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++x;

			--y;

			while (x <= 7 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O") {

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				--y;

			}

		}

	}

	if (j >= 1)

	{

		x = i;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			--y;

			while (y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--y;

			}

		}

	}
	if (i >= 1 && j >= 1)

	{

		x = i - 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			--x;

			--y;

			while (x >= 0 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				--y;

			}

		}

	}
	if (i >= 1)

	{

		x = i - 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			--x;

			while (x >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{

					return true;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

			}

		}

	}
	return false;
}


void ReversiGame::white_done(unsigned int i, unsigned int j){


	game_piece temp_white = {};
	temp_white.piece = white;
	temp_white.piece_name = "white reversi";
	temp_white.piece_representation = "O";




	int x = 0; 

	int y = 0; 

	int n = 0; 
	gameboard[width*j + i] = temp_white;


	if (i >= 1 && j <= 6)

	{
		x = i - 1;
		y = j + 1;


		if (gameboard[width*y + x].piece_representation == "X"){
			--x;

			++y;

			while (x >= 0 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = y - j - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y - 1) + (x + 1)] = temp_white;

						--y;

						++x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				++y;

			}

		}

	}

	if (j <= 6)

	{

		x = i;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++y;

			while (y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = y - j - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y - 1) + x] = temp_white;
						--y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++y;

			}

		}

	}

	if (i <= 6 && j <= 6)

	{

		x = i + 1;

		y = j + 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++x;

			++y;

			while (x <= 7 && y <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = y - j - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y - 1) + (x - 1)] = temp_white;

						--y;

						--x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				++y;

			}

		}

	}
	if (i <= 6)

	{

		x = i + 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++x;

			while (x <= 7)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = x - i - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*y + (x - 1)] = temp_white;

						--x;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

			}

		}

	}

	if (i <= 6 && j >= 1)

	{

		x = i + 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			++x;

			--y;

			while (x <= 7 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = x - i - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y + 1) + (x - 1)] = temp_white;

						--x;

						++y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				++x;

				--y;

			}

		}

	}

	if (j >= 1)

	{

		x = i;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{

			--y;

			while (y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = j - y - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y + 1) + x] = temp_white;

						++y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--y;

			}

		}

	}
	if (i >= 1 && j >= 1)

	{

		x = i - 1;

		y = j - 1;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			--x;

			--y;

			while (x >= 0 && y >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{
					n = j - y - 1;

					for (int k = 0; k < n; ++k)

					{
						gameboard[width*(y + 1) + (x + 1)] = temp_white;

						++x;

						++y;

					}

					break;

				}
				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}
				--x;

				--y;

			}

		}

	}
	if (i >= 1)

	{

		x = i - 1;

		y = j;
		if (gameboard[width*y + x].piece_representation == "X")

		{
			--x;

			while (x >= 0)

			{
				if (gameboard[width*y + x].piece_representation == "O")

				{


					n = i - x - 1;

					for (int k = 0; k < n; ++k)

					{

						gameboard[width*y + (x + 1)] = temp_white;

						++x;

					}

					break;

				}

				else if (gameboard[width*y + x].piece == no_color)

				{

					break;

				}


				--x;

			}

		}

	}

}






std::ostream &operator<< (std::ostream &out, const ReversiGame &n)
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
	out << "X 0 1 2 3 4 5 6 7" << std::endl;
	return out;

}