
#pragma once
#include <iostream>
#include "game_pieces.h"
#include "enumer.h"
#include <vector>
int read_dimensions(std::ifstream & stream, unsigned int & a, unsigned int & b);

int read_game_pieces(std::ifstream & stream, std::vector<game_piece> & vect, unsigned int & a, unsigned int & b);

void print_board(const std::vector<game_piece> & vect, unsigned int & width, unsigned int & height);