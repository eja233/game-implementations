/**
 * @file tictactoe.cpp
 * @author Elaine Arbaugh
 * @date January 2014
 * @copyright This code is in the public domain.
 * 
 * @brief Runs a game of metatictactoe.
 * 
 * Uses the Game class to run a game of metatictactoe. 
 */
#include "game.hpp"

/**
 * @brief Runs a game of metatictactoe.
 * 
 * Creates a new instance of a metatictactoe game and runs the game.
 */
int main(int argc, char ** argv) {
	Game *game = new Game();
	game->Run();
	return 0;
}
