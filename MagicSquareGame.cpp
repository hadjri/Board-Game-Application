#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "enumer.h"
#include "MagicSquareGame.h"
#include <algorithm>


MagicSquareGame::MagicSquareGame(int h, int v,
	game_pieces color, std::string name, std::string symbol, int lowestval) :GameBase(h, v, color, name, symbol, "","") {
	vector<string> strings;
	string line;
	ifstream ifs("MagicSquare.txt");
	if (ifs.is_open()) {
		
		while (getline(ifs, line)) {
			strings.push_back(line);
		}
	}
	for (int i = 1;i < 10;i++) {
		game_piece temp_piece = {};
		temp_piece.piece = magic_square;
		temp_piece.piece_name = "Magic square piece";
		temp_piece.piece_representation = to_string(i);
		available_pieces.push_back(temp_piece);
	}

	if (strings.size() == 0 ||  strings[1] == "NO DATA") {//allows the situation when no MagicSquare.txt exists


		//available pieces

		//filling with empty pieces:
		game_piece temp_piece_empty = {};
		temp_piece_empty.piece = no_color;
		temp_piece_empty.piece_name = "empty";
		temp_piece_empty.piece_representation = " ";


		for (int y = h - 1;y >= 0;y--) {
			for (int x = 0;x < v;x++) {
				int index = v * y + x;

				gameboard.push_back(temp_piece_empty);
			}
		}
		//cout << *this;
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
				temp_piece.piece = magic_square;
				temp_piece.piece_name = "Magic square piece";
				if (strings[v + 1 - i].at(j) != 'e') {
					temp_piece.piece_representation = strings[v + 1 - i].at(j);
				}
				else {
					temp_piece.piece_representation = " ";
					temp_piece.piece = no_color;

				}
				gameboard[index] = temp_piece;




			}
			cout << endl;
		}

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < gameboard.size(); ++j) {

				if (available_pieces[i].piece_representation == gameboard[j].piece_representation) {

					available_pieces[i] = temp_piece_empty;

				}

			}

		}

	}
	
}

ostream &operator<<(std::ostream &out, const MagicSquareGame &n) {
	out << endl;
	for (int y = n.height - 1;y >= 0;y--) {
		out << y;
		out << " ";
		for (int x = 0;x <n.width;x++) {
			int index = n.width * y + x;

			out << n.gameboard[index].piece_representation + " ";


		}
		out << std::endl << std::endl;
	}
	out << "X 0 1 2" << std::endl;
	out << endl;

	out << "Available pieces: ";
	for (int i = 0; i < 9; ++i) {
		if (n.available_pieces[i].piece_representation != "999") {
			out << n.available_pieces[i].piece_representation << " ";
		}
	}

	return out;

}

MagicSquareGame::~MagicSquareGame()
{
}

bool MagicSquareGame::done()
{

	int totalsize = height*width;
	
	for (int i = 0; i < totalsize; ++i)
	{

		if (gameboard[i].piece == no_color) //if empty pieces still on board return false
		{
			return false;
		}
	}
	
	//below we calculate the sum of each row in arays, as well as the diagonals
	int * columnsum = new int[width]();
	int * rowsum = new int[height]();
	int left_diagonal_sum = 0;
	int right_diagonal_sum = 0;
	cout << "HEIGHT: "<<height << endl;
	cout << "width: " << width << endl;
	//on the MagicSquare wiki, we are given informatoin about a magic constant.
	//it is computer below.
	int magicConstant = ((int(powf(double(height), 3.0)) -
		height + 2 * width*lowestvalue) / 2) + 3;

	//filling in column sum and row sum 
	for (int x = 0;x<width;++x)
	{
		
		for (int y = 0;y<height;++y)
		{
			
			columnsum[x] = columnsum[x] + stoi(gameboard[x*height + y].piece_representation);
			
		}
	}
	
	for (int x = 0;x<height;++x)
	{
		for (int y = 0;y<width;++y)
		{
			rowsum[x] = rowsum[x] + stoi(gameboard[x*height + y].piece_representation);

		}
	}


	//now for the diagonals:
	for (int i = 0;i<height;++i)
	{
		left_diagonal_sum = left_diagonal_sum + stoi(gameboard[i*width + i].piece_representation);

	}

	//Compute s_diagonal_RtL
	for (int i = 0;i<height;++i)
	{
		right_diagonal_sum = right_diagonal_sum +
			stoi(gameboard[i*width + width - i - 1].piece_representation);

	}

	bool flag = true;
	cout << "Magic: " << magicConstant;
	flag = flag && (left_diagonal_sum == magicConstant) &&
		(right_diagonal_sum == magicConstant);
	cout << "Flag1: " << flag;
	for (int i = 0; i<width;++i)
	{
		flag = flag && (rowsum[i] == magicConstant) &&
			(columnsum[i] == magicConstant);
	}
	cout << "Flag2: " << flag;
	return flag;

}



void MagicSquareGame::prompt(unsigned int & x)
{

	string userinput;

	bool validinput = false;// will be the  flag for our while loop 
	while (!validinput) {
		std::cout << "Please enter \'quit\' or one of the available pieces" << endl;
		string q = "quit";
		cin >> userinput;
		if (userinput == "quit") {
			validinput = true;
			throw q;
		}

		int userinputint = stoi(userinput);
		game_piece temp_piece = {};
		temp_piece.piece = magic_square;
		temp_piece.piece_name = " ";
		temp_piece.piece_representation = userinput;

		for (unsigned int i = 0;i < available_pieces.size();i++) {
			if (available_pieces[i].piece_representation == userinput) {


				x = userinputint;
				validinput = true;

			}


		}
	


	}

}

int MagicSquareGame::turn()
{
	unsigned int x, y, c;

	if (GameBase::prompt(x, y) == user_quit) {
		return user_quit;
	}
	try {
		prompt(c);
	}
	catch (...) {
		return user_quit;
	}
	//***********************************

	
	game_piece temp_piece_empty = {};
	temp_piece_empty.piece = no_color;
	temp_piece_empty.piece_name = " ";
	temp_piece_empty.piece_representation = "999";//false flag
												  //available_pieces.erase(available_pieces.begin() + c-1);

	available_pieces[c - 1] = temp_piece_empty;
	int index = width*y + x;

	game_piece temp_piece = {};
	temp_piece.piece = magic_square;
	temp_piece.piece_name = " ";
	temp_piece.piece_representation = to_string(c);


	gameboard[index] = temp_piece;
	
	print();
	
	return 0;
}



void MagicSquareGame::print()
{
	cout << *this << endl;
}

bool MagicSquareGame::stalemate()
{
	int totalsize = height*width;
	for (int i = 0; i < totalsize; ++i)
	{

		if (gameboard[i].piece == no_color) //if empty pieces still on board return false
		{
			return false;//if empty then must not be stalemate
		}
	}

	//below we calculate the sum of each row in arays, as well as the diagonals
	int * columnsum = new int[width]();
	int * rowsum = new int[height]();
	int left_diagonal_sum = 0;
	int right_diagonal_sum = 0;

	//on the MagicSquare wiki, we are given informatoin about a magic constant.
	//it is computer below.
	int magicConstant = (int(powf(double(height), 3.0)) -
		height + 2 * width*lowestvalue) / 2;

	//filling in column sum and row sum 
	for (int x = 0;x<width;++x)
	{
		for (int y = 0;y<height;++y)
		{
			columnsum[x] = columnsum[x] + stoi(gameboard[x*width + y].piece_representation);
		}
	}
	for (int x = 0;x<height;++x)
	{
		for (int y = 0;y<width;++y)
		{
			rowsum[x] = rowsum[x] + stoi(gameboard[x*height + y].piece_representation);
		}
	}


	//now for the diagonals:
	for (int i = 0;i<height;++i)
	{
		left_diagonal_sum = left_diagonal_sum + stoi(gameboard[i*width + i].piece_representation);
	}

	//Compute s_diagonal_RtL
	for (int i = 0;i<height;++i)
	{
		right_diagonal_sum = right_diagonal_sum +
			stoi(gameboard[i*width + width - i - 1].piece_representation);
	}

	bool flag = true;
	//this time the reverse as done.
	flag = flag && (left_diagonal_sum != magicConstant) &&
		(right_diagonal_sum != magicConstant);
	for (int i = 0; i<width;++i)
	{
		flag = flag && (rowsum[i] != magicConstant) &&
			(columnsum[i] != magicConstant);
	}
	return flag;
}
