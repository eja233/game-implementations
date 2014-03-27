/**
 * @file game.pp
 * @author Elaine Arbaugh
 * @date January 2014
 * @copyright This code is in the public domain.
 * 
 * @brief Class declaration for the game class. 
 * 
 * The game class implements a game of metatictactoe. It creates a board,
 * and then includes functions implementing the logic of different
 * parts of the game, including setup, showing the board state, and
 * taking a turn. Finally, the Run() function runs a complete game. 
 */
#include "game.hpp"
#include <iostream>
using namespace std;

/** 
 * @brief Constructor for the game class.
 * 
 * Creates a new game of metatictactoe by creating an empty board and
 * setting whose_turn, the variable that keeps track of whose_turn it
 * is, to 1, which corresponds to Player X. 
 * 
 * @param none
 * 
 * @return nothing
 */
Game::Game() {
	// Create a new instance of the larger board (bigboard) and the 
	// 9 smaller boards, one for each square of the larger board.
	bigboard = new Board();
	board0 = new Board();
	board1 = new Board();
	board2 = new Board();
	board3 = new Board();
	board4 = new Board();
	board5 = new Board();
	board6 = new Board();
	board7 = new Board();
	board8 = new Board();
	
	// Set the initial board value to be played on
	// to -1 for undetermined.
	which_board = -1;
	
	// Set whose_turn to the initial value of 1 for X. 
	whose_turn = 1;
} 

/**
 * @brief Destructor for the game class.
 * 
 * Since no memory is allocated for anything in this class, the
 * destructor doesn't need to do anything.
 * 
 * @param none
 * 
 * @return nothing
 */
Game::~Game() {
}

/** 
 * @brief Displays information necessary to play the game.
 * 
 * Explains the mechanics of how to play the game and how the
 * board works. 
 * 
 * @param none
 * 
 * @return nothing
 */
void Game::StartInfo() {
	// Display some initial information about the game. 
	// Print the boards for reference and information about how to 
	// play the game.
    cout << "+---------------------------------------+" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "|| 0 | 1 | 2 || 0 | 1 | 2 || 0 | 1 | 2 ||" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||" << endl;
    cout << "|| 3 | 4 | 5 || 3 | 4 | 5 || 3 | 4 | 5 ||" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||" << endl;
    cout << "|| 6 | 7 | 8 || 6 | 7 | 8 || 6 | 7 | 8 ||" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "|+-----------++-----------++-----------+|    +---+---+---+" << endl;
    cout << "|| 0 | 1 | 2 || 0 | 1 | 2 || 0 | 1 | 2 ||    | 0 | 1 | 2 |" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||    +---+---+---+" << endl;
    cout << "|| 3 | 4 | 5 || 3 | 4 | 5 || 3 | 4 | 5 ||    | 3 | 4 | 5 |" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||    +---+---+---+" << endl;
    cout << "|| 6 | 7 | 8 || 6 | 7 | 8 || 6 | 7 | 8 ||    | 6 | 7 | 8 |" << endl;
    cout << "|+-----------++-----------++-----------+|    +---+---+---+" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "|| 0 | 1 | 2 || 0 | 1 | 2 || 0 | 1 | 2 ||" << endl;
    cout << "||---+---+---||---+---+---||---+---+---||" << endl;
    cout << "|| 3 | 4 | 5 || 3 | 4 | 5 || 3 | 4 | 5 ||" << endl;
    cout << "||---+---+---||---+---+---||---+---+---||" << endl;
    cout << "|| 6 | 7 | 8 || 6 | 7 | 8 || 6 | 7 | 8 ||" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "This is a game of metatictactoe." << endl;
    cout << "This is the full board you are playing on." << endl;
    cout << "For reference, there is also a smaller board, " << endl;
    cout << "whose squares correspond to the big squares" << endl;
    cout << "in the larger board. Press enter to continue. " << endl;
    cin.ignore();
    
    cout << "Metatictactoe works as follows: Player X goes" << endl;
    cout << "first, and chooses one of the larger squares to" << endl;
    cout << "start on. He then picks a smaller square in" << endl;
    cout << "the large square to play on. This move is" << endl;
    cout << "recorded, and it is then player O's turn." << endl;
    cout << endl;
    cout << "Player O picks a smaller square in the large" << endl;
    cout << "square corresponding to the move in the smaller" << endl;
    cout << "square Player X chose. For instance, if an X" << endl;
    cout << "was played in square 1 of board 2, player" << endl;
    cout << "O must play an O somewhere in big square 1." << endl;
    cout << endl;
    cout << "If the board a player is supposed to play in is" << endl;
    cout << "full, the player may pick any board to play in." << endl;
    cout << endl;
    cout << "If a player gets 3 in a row on a smaller board," << endl;
    cout << "that board is marked with the player's symbol." << endl;
    cout << "To win the game, the player must get 3 boards" << endl;
    cout << "in a row. Press enter to start." << endl;
    // Wait for the user to press enter before continuing. 
    cin.ignore();
}

/**
 * @brief Prints the current state of the board. 
 * 
 * Gets values for each square of the board using board->Query()
 * and prints a game board representing these values. 
 * 
 * @param none
 * 
 * @return nothing
 */
void Game::PrintBoard() {
	// Print the current board states.
	cout << "+---------------------------------------+" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "|| " << board0->Query(0) << " | " << board0->Query(1);
    cout << " | " << board0->Query(2) << " || " << board1->Query(0);
    cout << " | " << board1->Query(1) << " | " << board1->Query(2);
    cout << " || " << board2->Query(0) << " | " << board2->Query(1);
    cout << " | " << board2->Query(2) << " ||" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||" << endl;
    cout << "|| " << board0->Query(3) << " | " << board0->Query(4);
    cout << " | " << board0->Query(5) << " || " << board1->Query(3);
    cout << " | " << board1->Query(4) << " | " << board1->Query(5);
    cout << " || " << board2->Query(3) << " | " << board2->Query(4);
    cout << " | " << board2->Query(5) << " ||" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||" << endl;
    cout << "|| " << board0->Query(6) << " | " << board0->Query(7);
    cout << " | " << board0->Query(8) << " || " << board1->Query(6);
    cout << " | " << board1->Query(7) << " | " << board1->Query(8);
    cout << " || " << board2->Query(6) << " | " << board2->Query(7);
    cout << " | " << board2->Query(8) << " ||" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "|+-----------++-----------++-----------+|    +---+---+---+" << endl;
    cout << "|| " << board3->Query(0) << " | " << board3->Query(1);
    cout << " | " << board3->Query(2) << " || " << board4->Query(0);
    cout << " | " << board4->Query(1) << " | " << board4->Query(2);
    cout << " || " << board5->Query(0) << " | " << board5->Query(1);
    cout << " | " << board5->Query(2) << " ||    | ";
    cout << bigboard->Query(0) << " | " << bigboard->Query(1) << " | ";
    cout << bigboard->Query(2) << " |" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||    +---+---+---+" << endl;
    cout << "|| " << board3->Query(3) << " | " << board3->Query(4);
    cout << " | " << board3->Query(5) << " || " << board4->Query(3);
    cout << " | " << board4->Query(4) << " | " << board4->Query(5);
    cout << " || " << board5->Query(3) << " | " << board5->Query(4);
    cout << " | " << board5->Query(5) << " ||    | ";
    cout << bigboard->Query(3) << " | " << bigboard->Query(4) << " | ";
    cout << bigboard->Query(5) << " |" << endl;
    cout << "||---+---+---||---+---+---++---+---+---||    +---+---+---+" << endl;
    cout << "|| " << board3->Query(6) << " | " << board3->Query(7);
    cout << " | " << board3->Query(8) << " || " << board4->Query(6);
    cout << " | " << board4->Query(7) << " | " << board4->Query(8);
    cout << " || " << board5->Query(6) << " | " << board5->Query(7);
    cout << " | " << board5->Query(8) << " ||    | ";
    cout << bigboard->Query(6) << " | " << bigboard->Query(7) << " | ";
    cout << bigboard->Query(8) << " |" << endl;
    cout << "|+-----------++-----------++-----------+|    +---+---+---+" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "|| " << board6->Query(0) << " | " << board6->Query(1);
    cout << " | " << board6->Query(2) << " || " << board7->Query(0);
    cout << " | " << board7->Query(1) << " | " << board7->Query(2);
    cout << " || " << board8->Query(0) << " | " << board8->Query(1);
    cout << " | " << board8->Query(2) << " ||" << endl;
    cout << "||---+---+---||---+---+---||---+---+---||" << endl;
    cout << "|| " << board6->Query(3) << " | " << board6->Query(4);
    cout << " | " << board6->Query(5) << " || " << board7->Query(3);
    cout << " | " << board7->Query(4) << " | " << board7->Query(5);
    cout << " || " << board8->Query(3) << " | " << board8->Query(4);
    cout << " | " << board8->Query(5) << " ||" << endl;
    cout << "||---+---+---||---+---+---||---+---+---||" << endl;
    cout << "|| " << board6->Query(6) << " | " << board6->Query(7);
    cout << " | " << board6->Query(8) << " || " << board7->Query(6);
    cout << " | " << board7->Query(7) << " | " << board7->Query(8);
    cout << " || " << board8->Query(6) << " | " << board8->Query(7);
    cout << " | " << board8->Query(8) << " ||" << endl;
    cout << "|+-----------++-----------++-----------+|" << endl;
    cout << "+---------------------------------------+" << endl;
}
	
/**
 * @brief Implements the logic of a turn. 
 * 
 * Prints the current game board. Determines which board the player
 * should be playing in. Prompts either player X or player O,
 * depending on the value of player, for a move. If the space is not
 * empty, prints an error message and prompts for input again. 
 * Otherwise, record the move using Board->Place.
 * 
 * @param player The player whose turn it is. 1 represents X and -1 
 *               represents O.
 * 
 * @return nothing
 */
void Game::Turn(int player) {
	int square_choice;
	bool is_valid = 0;
	string player_str;
	
	// Print the current game board. 
	PrintBoard();
	
	// Keep prompting for input until a valid move has been made. 
	while (is_valid == 0) {
		// Set a player_str to X if player is 1 and O if player is 
		// -1. 
		if (player == 1) {
			player_str = "X";
		}
		if (player == -1) {
			player_str = "O";
		}
		
		// If which_board is -1, corresponding to an undetermined 
		// board, prompt the player to enter which board they want to
		// play in.
		if (which_board == -1) {
			cout << "Which board do you want to play on, Player ";
			cout << player_str << "?" << endl;
			scanf("%d", &which_board);
		}
		
		
	    // Prompt a move. 
	    cout << "Where do you want to move in board " << which_board;
	    cout << ", Player " << player_str << "?" << endl;
	    scanf("%d", &square_choice);
	
	    // Make sure the space is empty. Otherwise, record the move,
	    // and set is_valid to 1 to exit the loop
	    if (which_board == 0) {
	        if (board0->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
			}
			
			else {
			    cout << "Move recorded." << endl;
			    board0->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board0->CheckWin() != 0) {
					bigboard->Place(0, board0->CheckWin());
				}
			    is_valid = 1;
		    }
		}
		
		else if (which_board == 1) {
	        if (board1->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board1->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board1->CheckWin() != 0) {
					bigboard->Place(1, board1->CheckWin());
				}
			    is_valid = 1;
			}
		}
		
		else if (which_board == 2) {
			if (board2->Query(square_choice) != " ") {
				cout << "Space is full. Try again!" << endl;
			}
			
			else {
				cout << "Move recorded." << endl;
				board2->Place(square_choice, player);
				// Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board2->CheckWin() != 0) {
					bigboard->Place(2, board2->CheckWin());
				}
				is_valid = 1;
			}
		}
		
		else if (which_board == 3) {
	        if (board3->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board3->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board3->CheckWin() != 0) {
					bigboard->Place(3, board3->CheckWin());
				}
			    is_valid = 1;
			}
		}
		
		else if (which_board == 4) {
	        if (board4->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board4->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board4->CheckWin() != 0) {
					bigboard->Place(4, board4->CheckWin());
				}
			    is_valid = 1;
			}
		}
		
		else if (which_board == 5) {
	        if (board5->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board5->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board5->CheckWin() != 0) {
					bigboard->Place(5, board5->CheckWin());
				}
			    is_valid = 1;
			}
		}
		
		else if (which_board == 6) {
	        if (board6->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board6->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board6->CheckWin() != 0) {
					bigboard->Place(6, board6->CheckWin());
				}
			    is_valid = 1;
		    }
		}
		
		else if (which_board == 7) {
	        if (board7->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board7->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board7->CheckWin() != 0) {
					bigboard->Place(7, board7->CheckWin());
				}
			    is_valid = 1;
			}
		}
		
		else if (which_board == 8) {
	        if (board8->Query(square_choice) != " ") {
			    cout << "Space is full. Try again!" << endl;
		    }
		    
		    else {
			    cout << "Move recorded." << endl;
			    board8->Place(square_choice, player);
			    // Check if the board has been won. If it has,
			    // set the corresponding space in the smaller 
			    // board to the corresponding value. 
			    if (board8->CheckWin() != 0) {
					bigboard->Place(8, board8->CheckWin());
				}
			    is_valid = 1;
			}
		}
    }
			
	// Set which_board to square_choice if the board is not
	// full. If the board is full, return -1 for an 
	// undetermined board. 
	if (square_choice == 0) {
        if (board0->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 1) {
        if (board1->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 2) {
        if (board2->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 3) {
        if (board3->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 4) {
        if (board4->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 5) {
        if (board5->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 6) {
        if (board6->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 7) {
        if (board7->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
    
    else if (square_choice == 8) {
        if (board8->CheckFull() == 0) {
			which_board = square_choice;
		}
		    
		else {
			which_board = -1;
		}
    }
	
}
	
/** 
 * @brief Runs the game of metatictactoe.
 * 
 * Prints starting information about the game, then implements
 * turns until the game ends in either a draw or a win. Prints 
 * a message corresponding to the final result of the game.
 * 
 * @param none
 * 
 * @return nothing
 */
void Game::Run() {
	// Counters to see who has won more spaces on the big board.
	int numX = 0;
	int numO = 0;
	// Print the intial information about the game.
	StartInfo();
	
	// Create new turns until there is either a draw or a win,
	// corresponding to the end of the game. 
	while ((bigboard->CheckDraw() == 0) && (bigboard->CheckWin() == 0)) {
		// Implement a turn. 
		Turn(whose_turn);
		
		// Change who the player who is having a turn is. If 
		// whose_turn is 1 (X), change it to -1 (O). If it is -1 (O), 
		// change it to 1 (X).
		if (whose_turn == 1) {
			whose_turn = -1;
		}
		else {
			whose_turn = 1;
		}
	}
	
	// Once the while loop exits, print information corresponding
	// to the final state of the game. 
	// Print the board and return a message if the game is a draw.
	if (bigboard->CheckDraw() == 1) {
		PrintBoard();
		for (int i = 0; i < 9; i++) {
			if (bigboard->Query(i) == "X") {
				numX += 1;
			}
			else if (bigboard->Query(i) == "O") {
				numO += 1;
			}
		}
		if (numX > numO) {
			cout << "The X player won!" << endl;
		}
		else if (numO > numX) {
			cout << "The O player won!" << endl;
		}
	}
	// Print the board and return a message if someone won.
	else if (bigboard->CheckWin() == 1) {
		PrintBoard();
		cout << "The X player won!" << endl;
	}
	else if (bigboard->CheckWin() == -1) {
		PrintBoard();
		cout << "The O player won!" << endl;
	}
}
		
		
		
