#pragma once
#include <vector>
#include <memory>
#include "game_pieces.h"
using namespace std;

class GameBase {
public:

	GameBase(unsigned int h, unsigned int w,
		game_pieces color, std::string name,
		std::string symbol, string p1, string p2);


	virtual ~GameBase() {};
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int &x, unsigned int &y);
	virtual void save_game(bool x);
	virtual int turn() = 0;
	virtual int play();
	static void creatptr(int argc, char * argv[]);
	static shared_ptr<GameBase> instance();

protected:
	game_pieces color;
	string name;
	int height;
	int width;
	string symbol;
	string player_1;
	string player_2;
	string whose_turn;
	int longestval;
	vector<game_piece> gameboard;
	static shared_ptr<GameBase> ptr;

};