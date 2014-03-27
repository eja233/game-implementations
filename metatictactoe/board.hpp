/**
 * @file board.hpp
 * @author Elaine Arbaugh
 * @date January 2014
 * @copyright This code is in the public domain.
 * 
 * @brief Header file for the board class. 
 * 
 * The board class implements function relevant to a metatictactoe 
 * board. It stores the board state in an array and includes 
 * function for finding a square's value, changing a square value,
 * and checking if the game has ended in a win or a draw or if the 
 * board is full.
 */
#include <string>

class Board {
	private:
	    int squares[9];
	public:
	    // Constructor
	    Board();
	    
	    // Destructor
	    ~Board();
	    
	    // Accessor
	    std::string Query(int coord);
	    
	    // Mutator
	    void Place(int coord, int value);
	    
	    // Other functions
	    int CheckWin();
	    
	    bool CheckFull();
	    
	    bool CheckDraw();
};
