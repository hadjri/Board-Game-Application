#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"
#include "ReversiGame.h"
#include "GameBase.h"
#include "enumer.h"

shared_ptr<GameBase> GameBase::ptr = nullptr;

using namespace std;
GameBase::GameBase(unsigned int h, unsigned int w,
	game_pieces color, std::string name,
	std::string symbol, string p1, string p2) : height(h), width(w), color(color), name(name), symbol(symbol), longestval(symbol.length()), player_1(p1), player_2(p2){}



shared_ptr<GameBase> GameBase::instance() {
	if (ptr!=nullptr) {
		return ptr;
	}
	else {
		throw no_instance;
	}
}
 


int GameBase::prompt(unsigned int &x, unsigned int &y) {

	string userinput;
	int a; // temp holding place for int value pair
int b;
bool validinput = false;// will be the  flag for our while loop 
int midax = 0;
int middleby = 0;

while (!validinput) {
	std::cout << "Please enter \'quit\' or a pair of integers seperated by a comma" << endl;

	cin >> userinput;
	if (userinput == "quit") {
		string savegame;
		cout << "Would you like to save the game?" << endl;
		cin >> savegame;
		if (savegame == "yes") {
			save_game(true);
			return user_quit;
		}
		else if(savegame == "no"){
			save_game(false);
		}
		else {
			throw bad_input;
		}


		validinput = true;
		return user_quit; // return value indicating user quit.
	}
	else {


		int commas = 0;
		int validcommand = 1;
		for (unsigned int i = 0; i < userinput.length(); ++i)
		{
			if (userinput[i] == ',')
			{
				++commas;
				userinput[i] = ' ';
			}
		}
		// Check if there is comma in the begining or in the end
		if (userinput[0] == ',' ||
			userinput[userinput.length() - 1] == ',')
		{
			validcommand = 0;
		}
		//define iss as istringstream
		istringstream iss(userinput);
		// check the input format and if it is correct, 
		// assign the value to int &a, int &b
		if (commas == 1 &&
			validcommand == 1 &&
			iss >> a && iss >> b)
		{
			//check the boundary
			if (a <= width - 1 &&
				b <= height - 1)
			{

				//set value of those to arguments.
				x = a;
				y = b;

				validinput = true;
				return success;
			}
			else
			{
				std::cout << "The input is out of boundary x <="
					<< width - 1 << " y <="
					<< height - 1 << endl;
			}
		}
	}
	std::cout << "Bad Input." << endl;
}
return bad_input; //should never reach this case.
}

void GameBase::save_game(bool x)
{
	int height = (*this).height;
	int width = (*this).width;
	string name = (*this).name;
	string gamename;
	cout << name << endl;
	if (name == "almond") {
		gamename = "NineAlmondsGame.txt";
	}
	if (name == "Magic") {
		gamename = "MagicSquare.txt";
	}
	if (name == "reversi") {
		gamename = "ReversiGame.txt";
	}



	ofstream stream(gamename.c_str());
	if (stream.is_open()) {
		if (x == true) {
			stream << gamename << endl;
			for (int i = height - 1; i+1 != 0;--i) {
				for (int j = 0; j < width; ++j) {
					if (gameboard[width*i + j].piece_representation == " ") {
						stream << "e";
					}
					else {
						stream << gameboard[width*i + j].piece_representation;
					}

				}
				stream << endl;
			}
			if(gamename == "ReversiGame.txt"){
				stream << whose_turn << endl;
			}
		}
		else {
			stream << gamename << endl;
			stream << "NO DATA" << endl;
		}





	}stream.close();

	
}


int GameBase::play() {
	
	whose_turn = player_1;
	bool isdone = false;
	int count = 0;
	print();
	while (!isdone) {
		int x = turn();
		if (x == user_quit) {
			cout << "USER: " << whose_turn << endl;
			//if(whose_turn = )
			cout << "User quit.  Number of turns taken: " << count;
			return user_quit;
		}

		if (whose_turn.compare(player_1) == 0) {
			whose_turn = player_2;
		}
		else   {
			whose_turn = player_1;
		}
		//first check to see ie user quit;
		
	
		count++;

		if (done()) {
			cout << "You win! Number of turns taken: " << count;
			isdone = true;
			return success;
		}
		if (stalemate()) {
			cout << "Stalemate! Game over. Number of turns taken: " << count << endl;
			return stalemate_game;
		}

	}

	return game_done; //program will not  ever make it here.
}

void GameBase::creatptr(int argc, char* argv[]) {
	
	if (ptr==nullptr) {
		cout << ptr << endl;
		if (argc == args && strcmp(argv[file_name], "MagicSquare") == 0) {
			
			shared_ptr<GameBase> temp (new MagicSquareGame(3, 3, magic_square, "Magic", "1"));
			ptr = temp;

		}
		else if ((argc == args) && (strcmp(argv[file_name], "NineAlmonds") == 0)) {
			shared_ptr<GameBase> temp (new NineAlmondsGame(5, 5, brown_almond, "almond", "A"));
			ptr = temp;

		}
		else if ((argc == args_reversi) && (strcmp(argv[file_name], "Reversi") == 0)) {
			
		
			string p1(argv[2]);
			string p2(argv[3]);

			shared_ptr<GameBase> temp(new ReversiGame(8, 8, reversi, "reversi", "X", p1,p2));
			ptr = temp;
			
		}
		else if (argc != args) {
			throw bad_argument;
		}
		else {
			throw wrong_name;
		}//gghgh
	}
	else {
		throw no_instance;
	}



}