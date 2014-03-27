/**
 * @file board.cpp
 * @author Elaine Arbaugh
 * @date January 2014
 * @copyright This code is in the public domain.
 * 
 * @brief Board class declaration file.  
 * 
 * The board class implements function relevant to a metatictactoe 
 * board. It stores the board state in an array and includes 
 * function for finding a square's value, changing a square value,
 * and checking if the game has ended in a win or a draw or if the 
 * board is full.
 */
#include "board.hpp"

/** 
 * @brief Consturctor for the Board class.
 * 
 * Creates a new instance of a board by initializing the squares
 * array, which holds the information for what is on each square,
 * to 0, corresponding to blank squares.
 * 
 * @param none
 * 
 * @return nothing
 */
Board::Board() {
	// Initialize squares to blank squares. 
	for (int i = 0; i < 9; i++) {
		squares[i] = 0;
	}
}

/**
 * @brief Destructor for the Board class.
 * 
 * Deletes the array of squares.
 * 
 * @param none
 * 
 * @return nothing
 */
Board::~Board() {
    delete[] squares;
}

/**
 * @brief Returns the state of the input square.
 * 
 * X, O, and blank squares are represented by 1, -1, and 0,
 * respectively. For an input square value, check the value of
 * squares at that position, and output X for 1, O for -1, and an
 * empty string for 0. 
 * 
 * @param coord The coordinate, between 0 and 8, we want information 
 *              for.
 * 
 * @return A string representing the value at the coordinate.
 */
std::string Board::Query(int coord) {
	if (squares[coord] == 0) {
		return " ";
	}
	else if (squares[coord] == 1) {
		return "X";
	}
	else {
		return "O";
	}
}

/**
 * @brief Places a game piece on the board.
 * 
 * Takes an input coordinate and value and places that value at that
 * position in the squares array.
 * 
 * @param coord The coordinate where we want to put a value.
 * @param value The value we want to place there.
 * 
 * @return nothing
 */
void Board::Place(int coord, int value) {
    // Set the specified place on the board to the specified value.
    squares[coord] = value;
}

/**
 * @brief Checks if either player has won.
 * 
 * Checks if a winning combination has been achieved by
 * going through every possible winning configuration. 
 * If a winning configuration has been achieved, return the value 
 * of squares[] at that point, which corresponds to the player
 * who won, with 1 being X and -1 being O. Otherwise, return 0
 * for a nonwinning configuration.
 * 
 * @param none
 * 
 * @return 1 for X winning, -1 for O winning, or 0 for a draw.
 */
int Board::CheckWin() {
	// Check if any of the possible winning combinations were
	// achieved. If there are three of either Xs or Os, return the
	// value of one of the squares, which corresponds to the player.
	// 1 represents X, -1 represents O.
	// Check if all spaces on a column have the same value.
	if ((squares[0] == squares[3]) && (squares[0] == squares[6]) 
	    && (squares[0] != 0)) {
		    return squares[0];
    }
    else if ((squares[1] == squares[4]) && (squares[1] == squares[7]) 
             && (squares[1] != 0)) {
		    return squares[1];
	}
	else if ((squares[2] == squares[5]) && (squares[2] == squares[8])
	         && (squares[2] != 0)) {
		   return squares[2];
	}
	// Check if all spaces in a row have the same value.
	else if ((squares[0] == squares[1]) && (squares[0] == squares[2])
	         && (squares[2] != 0)) {
		return squares[0];
	}
	else if ((squares[3] == squares[4]) && (squares[3] == squares[5])
	         && (squares[3] != 0)) {
		return squares[3];
	}
	else if ((squares[6] == squares[7]) && (squares[6] == squares[8])
	         && (squares[6] != 0)) {
		return squares[6];
	}
	// Check if all spaces on a diagonal have the same value. 
	else if ((squares[0] == squares[4]) && (squares[0] == squares[8])
	         && (squares[0] != 0)) {
		return squares[0];
	}
	else if ((squares[2] == squares[4]) && (squares[2] == squares[6])
	         && (squares[2] != 0)) {
		return squares[2];
	}
	// Return 0 if none of the winning configurations happened. 
	return 0;
}

/** 
 * @brief Checks if the board is full.
 * 
 * Loops through the squares in the board and checks if any 
 * spaces are empty.
 * 
 * @param none
 * 
 * @return 1 for full, 0 for not full.
 */
bool Board::CheckFull() {
	for (int i = 0; i < 9; i++) {
		// If any of the squares have values 0, the board has 
		// empty spaces, so is not full. Return 0.
		if (squares[i] == 0) {
			return 0;
		}
    }
    // Otherwise, the square is full. Return 1. 
	return 1;
}

/** 
 * @brief Checks if the current game configuration is a draw.
 * 
 * Checks if someone won, because if someone won, it is not a draw.
 * Then checks if all the spaces have been filled, because if there
 * are open spaces, the game is not over. Otherwise, returns that a
 * the game is a draw.
 * 
 * @param none
 * 
 * @return 1 for a draw, 0 for not a draw.
 */
bool Board::CheckDraw() {
	// Check if someone won. If someone won, it is not a draw. 
	if (CheckWin() == 0) {
		// Check if all the spaces have been filled. If they are
		// full and there is no win, it is a draw. Return 1.
		if (CheckFull() == 1) {
			return 1;
		}
		// Otherwise, the spaces are not full. Return 0.
		else {
		    return 0;
		}
	}
	// If someone won, return 0 for not a draw. 
	else {
		return 0;
	}
}
