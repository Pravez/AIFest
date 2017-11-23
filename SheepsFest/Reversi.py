RED = "\033[1;31m"
BLUE = "\033[1;34m"
CYAN = "\033[1;36m"
GREEN = "\033[0;32m"
RESET = "\033[0;0m"
BOLD = "\033[;1m"
REVERSE = "\033[;7m"


class Board:
    _BLACK = 1
    _WHITE = 2
    _EMPTY = 0

    def __init__(self):
        self._board = []
        self._nbWHITE = 2
        self._nbBLACK = 2
        self._nextPlayer = self._BLACK
        for x in range(8):
            self._board.append([self._EMPTY] * 8)
        self._board[3][3] = self._BLACK
        self._board[3][4] = self._WHITE
        self._board[4][3] = self._WHITE
        self._board[4][4] = self._BLACK
        self._lastPlay = (0, 0)
        self._changedPiecesLastPlay = []

        self._stack = []

    def reset(self):
        self.__init__()

    def is_valid_move(self, player, x, y):
        return self.lazyTest_ValidMove(self, player, x, y)

    def _isOnBoard(self, x, y):
        return x >= 0 and x <= 7 and y >= 0 and y <= 7

    # Renvoie la liste des pieces a retourner si le coup est valide
    # Sinon renvoie False
    # Ce code est très fortement inspiré de https://inventwithpython.com/chapter15.html
    # y faire référence dans tous les cas
    def testAndBuild_ValidMove(self, player, xstart, ystart):
        if self._board[xstart][ystart] != self._EMPTY or not self._isOnBoard(xstart, ystart):
            return False

        # On pourra remettre _EMPTY ensuite
        self._board[xstart][ystart] = player

        otherPlayer = self._flip(player)

        # Si au moins un coup est valide, on collecte ici toutes les pieces a retourner
        tilesToFlip = []
        for xdirection, ydirection in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
            x, y = xstart, ystart
            x += xdirection
            y += ydirection
            if self._isOnBoard(x, y) and self._board[x][y] == otherPlayer:
                # There is a piece belonging to the other player next to our piece.
                x += xdirection
                y += ydirection
                if not self._isOnBoard(x, y):
                    continue
                while self._board[x][y] == otherPlayer:
                    x += xdirection
                    y += ydirection
                    # break out of while loop, then continue in for loop
                    if not self._isOnBoard(x, y):
                        break
                if not self._isOnBoard(x, y):
                    continue
                # We are sure we can at least build this move. Let's collect
                if self._board[x][y] == player:
                    while True:
                        x -= xdirection
                        y -= ydirection
                        if x == xstart and y == ystart:
                            break
                        tilesToFlip.append([x, y])

        self._board[xstart][ystart] = self._EMPTY  # restore the empty space
        # If no tiles were flipped, this is not a valid move.
        if len(tilesToFlip) == 0:
            return False
        return tilesToFlip

    # Pareil que ci-dessus mais ne revoie que vrai / faux (permet de tester plus rapidement)
    def lazyTest_ValidMove(self, player, xstart, ystart):
        if self._board[xstart][ystart] != self._EMPTY or not self._isOnBoard(xstart, ystart):
            return False

        # On pourra remettre _EMPTY ensuite
        self._board[xstart][ystart] = player

        otherPlayer = self._flip(player)

        for xdirection, ydirection in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
            x, y = xstart, ystart
            x += xdirection
            y += ydirection
            if self._isOnBoard(x, y) and self._board[x][y] == otherPlayer:
                # There is a piece belonging to the other player next to our piece.
                x += xdirection
                y += ydirection
                if not self._isOnBoard(x, y):
                    continue
                while self._board[x][y] == otherPlayer:
                    x += xdirection
                    y += ydirection
                    # break out of while loop, then continue in for loop
                    if not self._isOnBoard(x, y):
                        break
                if not self._isOnBoard(x, y):  # On a au moins
                    continue
                # We are sure we can at least build this move.
                if self._board[x][y] == player:
                    self._board[xstart][ystart] = self._EMPTY
                    return True

        self._board[xstart][ystart] = self._EMPTY  # restore the empty space
        return False

    def _flip(self, player):
        if player == self._BLACK:
            return self._WHITE
        return self._BLACK

    def heuristique(self, player=None):
        if player is None:
            player = self._nextPlayer
        if player is self._WHITE:
            return self._nbWHITE - self._nbBLACK
        return self._nbBLACK - self._nbWHITE

    def is_game_over(self):
        # if self.at_least_one_legal_move(self._nextPlayer):
        #     return False
        # if self.at_least_one_legal_move(self._flip(self._nextPlayer)):
        #     return False
        # return True
        return self._nbWHITE + self._nbWHITE == 64

    def push(self, move):
        [player, x, y] = move
        self._lastPlay = (x, y)
        if x == -1 and y == -1:  # pass
            self._nextPlayer = self._flip(player)
            self._stack.append([move, []])
            return
        toflip = self.testAndBuild_ValidMove(player, x, y)
        self._stack.append([move, toflip])
        self._board[x][y] = player
        self._changedPiecesLastPlay = toflip
        for xf, yf in toflip:
            self._board[xf][yf] = self._flip(self._board[xf][yf])
        if player == self._BLACK:
            self._nbBLACK += 1 + len(toflip)
            self._nbWHITE -= len(toflip)
            self._nextPlayer = self._WHITE
        else:
            self._nbWHITE += 1 + len(toflip)
            self._nbBLACK -= len(toflip)
            self._nextPlayer = self._BLACK

    def pop(self):
        [move, toflip] = self._stack.pop()
        [player, x, y] = move
        if len(toflip) == 0:  # pass
            self._nextPlayer = self._flip(player)
            return
        self._board[x][y] = self._EMPTY
        for xf, yf in toflip:
            self._board[xf][yf] = self._flip(self._board[xf][yf])
        if player == self._BLACK:
            self._nbBLACK -= 1 + len(toflip)
            self._nbWHITE += len(toflip)
            self._nextPlayer = self._WHITE
        else:
            self._nbWHITE -= 1 + len(toflip)
            self._nbBLACK += len(toflip)
            self._nextPlayer = self._BLACK

    def legal_moves(self):
        moves = []
        for x in range(0, 8):
            for y in range(0, 8):
                if self.lazyTest_ValidMove(self._nextPlayer, x, y):
                    moves.append([self._nextPlayer, x, y])
        if len(moves) is 0:
            moves = [[self._nextPlayer, -1, -1]]  # We shall pass
        return moves

    def _piece2str(self, c):
        if c == self._WHITE:
            return 'O'
        elif c == self._BLACK:
            return 'X'
        else:
            return '.'

    def __str__(self):
        toreturn = ""
        for x in range(0, 8):
            for y in range(0, 8):
                if (x, y) == self._lastPlay:
                    toreturn += RED + self._piece2str(self._board[x][y]) + RESET
                else:
                    toreturn += self._piece2str(self._board[x][y])
            toreturn += "\n"
        return toreturn

    __repr__ = __str__
