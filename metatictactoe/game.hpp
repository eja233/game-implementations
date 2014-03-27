/**
 * @file game.hpp
 * @author Elaine Arbaugh
 * @date January 2014
 * @copyright This code is in the public domain.
 * 
 * @brief Header file for the game class. 
 * 
 * The game class implements a game of metatictactoe. It creates a board,
 * and then includes functions implementing the logic of different
 * parts of the game, including setup, showing the board state, and
 * taking a turn. Finally, the Run() function runs a complete game. 
 */
#include "board.hpp"

class Game {
	private:
	    Board * board0;
	    Board * board1;
	    Board * board2;
	    Board * board3;
	    Board * board4;
	    Board * board5;
	    Board * board6;
	    Board * board7;
	    Board * board8;
	    Board * bigboard;
	    int which_board;
	    int whose_turn;
	    
	public:
	    // Constructor
	    Game();
	    
	    // Destructor
	    ~Game();
	   
	    // Other functions
	    void StartInfo();
	    void PrintBoard();
	    void Turn(int player);
	    void Run();
};
