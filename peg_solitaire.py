# Elaine Arbaugh
# 12/15/12
# Part of my final exam for an intro to python class: implementation of a peg solitaire game playable
# from the command line. We were given a template file which had the show function, but I wrote the
# rest of the code. 
'''
Interactive peg solitaire game.
'''

import sys

class SolitaireError(Exception):
    '''Error class for Solitaire errors.'''
    pass

class Solitaire:
    '''Interactive peg solitaire game.'''
    def __init__(self, pegs=None):
        '''Creates the board representation as a list of lists with -1 
        representing an empty space, 0 representing an open space, and 1 
        representing a peg. If an argument is supplied, the coordinates in it
        are the initial configuration for the pegs.'''
        self.board = []
        # Initialize the board with 0s in all positions.
        for i in range(2):
            self.board.append([-1] * 2 + [0] * 3 + [-1] * 2)
        for i in range(3):
            self.board.append([0] * 7)
        for i in range(2):
            self.board.append([-1] * 2 + [0] * 3 + [-1] * 2)
        if pegs == None:
            # Create the default starting position.
            for i in range(2) + range(5, 7):
                for j in range(2, 5):
                    self.board[i][j] = 1
            for i in range(7):
                self.board[2][i] = 1
                self.board[4][i] = 1
            for i in range(3) + range(4, 7):
                self.board[3][i] = 1
            self.board[3][3] = 0
        else:
            # Create a non-standard starting position.
            if type(pegs) is not list:
                raise TypeError('Argument must be a list of tuples')
            for item in pegs:
                if type(item) is not tuple:
                    raise TypeError('Argument must be a list of tuples')
                if len(item) != 2:
                    raise ValueError('Each tuple must consist of two' + \
                                     ' integers in the range 0 to 6')
                if type(item[0]) is not int or type(item[1]) is not int:
                    raise TypeError('Tuple must consist of integers')
                if item[0] not in range(7) or item[1] not in range(7):
                    raise ValueError('Each tuple must consist of two' + \
                                     ' integers in the range 0 to 6')
            for item in pegs:
                self.board[item[0]][item[1]] = 1
        self.moves = []
                    
    def show(self):
        '''Prints the current board representation.'''
        print '    0 1 2 3 4 5 6'
        print '  +---------------+'
        for i in range(7):
            sys.stdout.write('%d | ' % i)
            for j in range(7):
                if self.board[i][j] == -1:
                    sys.stdout.write('  ')
                if self.board[i][j] == 0:
                    sys.stdout.write('. ')
                if self.board[i][j] == 1:
                    sys.stdout.write('O ')
            sys.stdout.write('|\n')
        print '  +---------------+'
                
    def showMoves(self):
        '''Prints out a list of the moves that can be made on the current 
        board.'''
        moves = self.currentMoves()
        counter = 0
        for item in moves:
            if self.board[item[0][0]][item[0][1]] == 1:
                print('move ' + str(counter) + ': jump from ' + str(item[0]) + \
                      ' to ' + str(item[2]))
            elif self.board[item[0][0]][item[0][1]] == 0:
                print('move ' + str(counter) + ': jump from ' + str(item[2]) + \
                      ' to ' + str(item[0]))
            counter += 1

    def allMoves(self):
        '''Computes a list of all the theoretically possible moves on a 
        board.'''
        moves = []
        for i in range(7):
            for j in range(7):
                if self.board[i][j] != -1:
                    if i < 5:
                        if self.board[i + 2][j] != -1:
                            moves.append(((i, j), (i + 1, j), (i + 2, j)))
                            moves.append(((i + 2, j), (i + 1, j), (i, j)))
                    if j < 5:
                        if self.board[i][j + 2] != -1:
                            moves.append(((i, j), (i, j + 1), (i, j + 2)))
                            moves.append(((i, j + 2), (i, j + 1), (i, j)))
        return moves        

    def currentMoves(self):
        '''Returns a list of the moves that can be made on the current board.'''
        all_moves = self.allMoves()
        moves = []
        for item in all_moves:
            if self.board[item[1][0]][item[1][1]] == 1:
                if self.board[item[0][0]][item[0][1]] == 1:
                    if self.board[item[2][0]][item[2][1]] == 0:
                        moves.append(item)
        return moves
                
    def makeMove(self, move):
        '''Takes a move as an argument and makes the move.'''
        assert self.board[move[0][0]][move[0][1]] == 1
        assert self.board[move[1][0]][move[1][1]] == 1
        assert self.board[move[2][0]][move[2][1]] == 0
        self.board[move[0][0]][move[0][1]] = 0
        self.board[move[1][0]][move[1][1]] = 0
        self.board[move[2][0]][move[2][1]] = 1
        self.moves.append(move)
        
    def undoMove(self):
        '''Undoes the last move.'''
        if len(self.moves) > 0:
            move = self.moves.pop()
            for i in move:
                if self.board[i[0]][i[1]] == 0:
                    self.board[i[0]][i[1]] = 1
                    continue
                elif self.board[i[0]][i[1]] == 1:
                    self.board[i[0]][i[1]] = 0
                
    def play(self):
        '''Prints the board, the list of possible moves, prompts the user
        to enter a command, and executes the command in an infinite loop.'''
        try:
            while True:
                self.show()
                self.showMoves()
                move_choice = raw_input('solitaire> ')
                if move_choice == 'q':
                    print 'Quitting game...'
                    return
                if move_choice == 'u':
                    print 'Undoing last move...'
                    self.undoMove()
                if move_choice[0] in '0123456789':
                    moves_list = self.currentMoves()
                    if int(move_choice) not in range(len(moves_list)):
                        raise SolitaireError('Move number is not an option')
                    else:
                        self.makeMove(moves_list[int(move_choice)])
                else:
                    raise SolitaireError('Command is not recognized')
        except SolitaireError, e:
            print e
            self.play()
            
if __name__ == '__main__':
    # "Fireplace" configuration.
    fireplace_board = [(0, 2), (0, 3), (0, 4),
                       (1, 2), (1, 3), (1, 4),
                       (2, 2), (2, 3), (2, 4),
                       (3, 2), (3, 4)]
    # Play the game twice, once with the fireplace configuration
    # and once with the default starting board configuration.
    s = Solitaire(fireplace_board)
    s.play()
    s = Solitaire()
    s.play()

