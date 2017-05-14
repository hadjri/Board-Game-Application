#pragma once
#include <string>

enum game_pieces { red, black, white, brown_almond, magic_square, reversi, invalid_color, no_color, x_reversi, o_reversi };

std::string piece_to_string(game_pieces x);

game_pieces string_to_piece(std::string x);

struct game_piece {
	game_pieces piece;
	std::string piece_name, piece_representation;

};
