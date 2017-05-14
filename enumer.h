#pragma once



enum index { program_name, file_name, args, name, args_reversi };

enum status {
	success, failure_file_not_found, wrong_number_of_commands, no_piece_read,
	no_line_read, read_line_no_dimensions, user_quit, bad_input, turn_over, stalemate_game, game_done, bad_mem, no_instance, bad_argument, wrong_name
};