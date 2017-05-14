#pragma once
#include "game_board.h"
#include "gameBase.h"
#include "game_pieces.h"
#include "enumer.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;




class ReversiGame : public GameBase {

	friend std::ostream &operator<<(std::ostream &out, const ReversiGame &n);
	//constructor

public:
	ReversiGame(unsigned int h, unsigned int v,
		game_pieces color, std::string name, std::string symbol, string p1, string p2);

	virtual ~ReversiGame() {};

	virtual bool done();

	virtual bool no_moves();

	virtual bool stalemate();

	virtual void print();

	virtual int turn();

	bool w_available_square();

	bool b_available_square();

	void white_done(unsigned int i, unsigned int j);

	void black_done(unsigned int i, unsigned int j);

	bool available_move_black(unsigned int i, unsigned int j);

	bool available_move_white(unsigned int i, unsigned int j);



protected:
	string player1;
	string player2;
	string whoseturn;
	int count_x;
	int count_o;


};
