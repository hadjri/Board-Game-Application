#pragma once
#include "game_board.h"
#include "gameBase.h"
#include "game_pieces.h"
#include "enumer.h"
#include <string>
#include <vector>
#include <iostream>

//THINK ABOUT hwo to structuer class. watch vide on classes and look at old thing. maybe stick w struct maybe not
class NineAlmondsGame : public GameBase {

	friend std::ostream &operator<<(std::ostream &out, const NineAlmondsGame &n);
	//constructor

public:
	NineAlmondsGame(unsigned int h, unsigned int v,
		game_pieces color, std::string name, std::string symbol);
	virtual ~NineAlmondsGame() {}
	virtual bool done();
	//virtual void save_game();
	virtual bool stalemate();

	//virtual int prompt(unsigned int &x, unsigned int &y);
	virtual void print();

	virtual int turn();



	// hold the game pieces, representign a gameboard
	// the index correspond to the position of the board as per the last lab.
protected:
	//	std::vector<game_piece> gameboard;
	//	unsigned int height;
	//	unsigned int width;

};