#ifndef _MAGICSQUAREGAME_H
#define _MAGICSQUAREGAME_H
#include "GameBase.h"
class MagicSquareGame : public GameBase {

	friend std::ostream &operator<<(std::ostream &out, const MagicSquareGame &n);

public:

	MagicSquareGame(int h, int v,
		game_pieces color, std::string name, std::string symbol, int lowestval = 1);

	virtual ~MagicSquareGame();

	virtual bool done();

	virtual void prompt(unsigned int &x);
	virtual int turn();
	virtual void print();
	virtual bool stalemate();
	
protected:
	int lowestvalue;

	vector<game_piece> available_pieces;

};

#endif