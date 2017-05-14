#include "stdafx.h"
#include "game_pieces.h"
#include <algorithm>

std::string piece_to_string(game_pieces x) {

	if (x == red) {
		return "red";
	}
	if (x == brown_almond) {
		return "A";
	}
	if (x == black) {
		return "black";
	}
	if (x == white) {
		return "white";
	}

	if (x == no_color) {
		return "no color";
	}
	return "invalid color";  //default if does not match any of the above.
}

game_pieces string_to_piece(std::string x) {
	if (x == "red") {
		return red; //
	}
	if (x == "white") {
		return white; //
	}
	if (x == "black") {
		return black; //
	}
	if (std::all_of(x.begin(), x.end(), isspace)) {//this will evalutte to true if whitespace string is passed
		return no_color;
	}
	return invalid_color;//if none of these are true, and an inorrect string is passed we return invalid_color.
}