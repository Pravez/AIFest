import time
import Reversi
from random import randint


#### FONCTION HEURISTIQUE ####
def evalBoard(b):
    return b.heuristique()


def deroulementRandom(b):
    print("----------")
    print(b)
    if b.is_game_over():
        return
    moves = [m for m in b.legal_moves()]
    assert len(moves) > 0
    move = moves[randint(0, len(moves) - 1)]
    b.push(move)
    deroulementRandom(b)
    b.pop()


def RandomMove(b):
    moves = [m for m in b.legal_moves()]
    move = moves[randint(0, len(moves) - 1)]
    return move


nbnodes = 0

######### ALPHA BETA #############

maxCPU = None


def IDAlphaBeta(board, maxTime=5):
    global maxCPU
    maxCPU = time.perf_counter() + maxTime
    thisDepth = 1
    res = None
    t = 0
    while True:
        try:
            t = time.perf_counter()
            res = IAAlphaBeta(board, maxdepth=thisDepth)
            t = time.perf_counter() - t
        except TimeoutError:
            return res
        #print(" Profondeur ", thisDepth, " Ok (", t, "s)")
        thisDepth += 1


def IAAlphaBeta(b, maxdepth=3):
    global nbnodes
    nbnodes += 1
    alpha = -800  # Dans ce jeu, 800 est l'infini
    meilleurcoup = None
    moves = [m for m in b.legal_moves()]
    for move in moves:  # Pas de coupe au premier niveau (par construction)
        b.push(move)
        try:
            v = Minvalue(b, alpha, 800, maxdepth - 1)
        except TimeoutError:
            b.pop()
            raise TimeoutError
        if v > alpha or meilleurcoup is None:
            alpha = v
            meilleurcoup = move
        b.pop()
    return meilleurcoup


def Maxvalue(b, alpha, beta, maxdepth=3):
    global nbnodes
    nbnodes += 1
    if time.perf_counter() > maxCPU:
        raise TimeoutError
    if b.is_game_over():
        return 400
    if maxdepth == 0:
        return evalBoard(b)
    moves = [m for m in b.legal_moves()]
    for move in moves:
        b.push(move)
        try:
            v = Minvalue(b, alpha, beta, maxdepth - 1)
        except TimeoutError:
            b.pop()
            raise TimeoutError
        b.pop()
        if v > alpha:
            alpha = v
        if alpha >= beta:
            return beta  # Coupe beta
    return alpha


def Minvalue(b, alpha, beta, maxdepth=3):
    global nbnodes
    nbnodes += 1
    if time.perf_counter() > maxCPU:
        raise TimeoutError
    if b.is_game_over():
        return -400
    if maxdepth == 0:
        return evalBoard(b)
    moves = [m for m in b.legal_moves()]
    for move in moves:
        b.push(move)
        try:
            v = Maxvalue(b, alpha, beta, maxdepth - 1)
        except TimeoutError:
            b.pop()
            raise TimeoutError
        b.pop()
        if v < beta:
            beta = v
        if alpha >= beta:
            return alpha  # Coupe Alpha
    return beta


######### MINIMAX ################
# IA utilisant Minimax
# MaxMin special pour récupérer le coup associé au meilleur (et non pas juste sa valeur)
def IAMinimax(b, maxdepth=3):
    global nbnodes
    nbnodes += 1
    meilleur = -800
    meilleurcoup = None
    moves = [m for m in b.legal_moves()]
    for move in moves:
        b.push(move)
        v = Minmax(b, maxdepth - 1)
        if v > meilleur or meilleurcoup is None:
            meilleur = v
            meilleurcoup = move
        b.pop()
    return meilleurcoup


def NegaMax(b, maxdepth=3):
    global nbnodes
    nbnodes += 1
    if maxdepth == 0 or b.is_game_over():
        return 400
    if maxdepth == 0:
        return evalBoard(b)
    meilleur = -800
    moves = [m for m in b.legal_moves()]
    for move in moves:
        b.push(move)
        v = -NegaMax(b, maxdepth - 1)
        if v > meilleur:
            meilleur = v
        b.pop()
    return meilleur


def Maxmin(b, maxdepth=3):
    global nbnodes
    nbnodes += 1
    if b.is_game_over():
        return 400
    if maxdepth == 0:
        return evalBoard(b)
    meilleur = -800
    moves = [m for m in b.legal_moves()]
    for move in moves:
        b.push(move)
        v = Minmax(b, maxdepth - 1)
        if v > meilleur:
            meilleur = v
        b.pop()
    return meilleur


def Minmax(b, maxdepth=3):
    global nbnodes
    nbnodes += 1
    if b.is_game_over():
        return -400
    if maxdepth == 0:
        return evalBoard(b)
    pire = +800
    moves = [m for m in b.legal_moves()]
    for move in moves:
        b.push(move)
        v = Maxmin(b, maxdepth - 1)
        if v < pire:
            pire = v
        b.pop()
    return pire

# Match :


board = Reversi.Board()
print("Le grand match IA vs Random !")
print(board)
nbcoups = 0

while not board.is_game_over():
    tt = time.perf_counter()
    coup = IDAlphaBeta(board, 3)  # Profondeur donnée en "secondes" pour ID
    print("ID-ab joue " + str(coup) + " en " + str(time.perf_counter() - tt))
    board.push(coup)
    #print(board)
    #time.sleep(5)

    tt = time.perf_counter()
    coup = IAMinimax(board, 3)  # Profondeur donnée en nombre de coups
    print("IA-MiniMax joue " + str(coup) +
          " en " + str(time.perf_counter() - tt))
    board.push(coup)

    print(board)
