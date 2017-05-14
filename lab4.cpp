// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game_pieces.h"
#include "game_board.h"
#include "NineAlmondsGame.h"
#include "usage.h"
#include <fstream>
#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{

	shared_ptr<GameBase> ptr;
	try {

		GameBase::creatptr(argc, argv);
		ptr = GameBase::instance();
		ptr->play();
		
	}
	catch (bad_alloc & all) {

		return bad_mem;
	}
	catch (...) { //more than bad_alloc may be thrown during program execution. --cw
		return -2;  //bad hack, don't use a const directly like this --cw
	}



	return success;
}


