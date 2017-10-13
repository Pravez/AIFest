import time
import chess
from random import randint


def deroulement(b, maxdepth=10):
    print("----------")
    print(b)
    if maxdepth is 0 or b.is_game_over():
        return
    for move in b.legal_moves:
        b.push(move)
        deroulement(b, maxdepth - 1)
        b.pop()


def deroulementRandom(b):
    print("----------")
    print(b)
    if b.is_game_over():
        return
    moves = [m for m in b.legal_moves]
    assert len(moves) > 0
    move = moves[randint(0, len(moves) - 1)]
    b.push(move)
    deroulementRandom(b)
    b.pop()


# ""
# BOARD EVALUATION

def board2tab(b):
    return [x.split(' ') for x in str(b).split('\n')]


valpieces = {'.': 0, 'P': 1, 'R': 5, 'N': 3, 'B': 3, 'Q': 9, 'K': 200}


def evalpiece(p):
    if p == p.upper():  # Blanc
        return valpieces[p]
    else:
        return -valpieces[p.upper()]


def evalBoard(b):
    score = 0
    tab = board2tab(b)
    for l in tab:
        for p in l:
            score += evalpiece(p)
    return score


# ""
# Votre code de MiniMax et plus tard Alpha Beta ici
# IA

def evalEnemyTurn(b, maxdepth=3):
    print("Enemy Turn " + str(3 - maxdepth))
    print(b)

    
    if b.is_game_over():
        return [100, '']
    if maxdepth == 0:
        return [evalBoard(b), '']
    worst = 100
    temp = [worst, '']
    enemy_moves = [move for move in b.legal_moves]
    for m in enemy_moves:
        b.push(m)
        result = evalFriendTurn(b, maxdepth - 1)
        b.pop()
        # print("If ally plays ")
        # print(m)
        # print(" best value is "+str(result))
        if result[0] < worst:
            worst = result[0]
            temp = [worst, m]
    # print("Worst is "+str(worst))
    if temp[1] == '' or board.can_claim_threefold_repetition():
        temp[1] = enemy_moves[randint(0, len(enemy_moves)-1)]
    return temp


def evalFriendTurn(b, maxdepth=3):
    print("Friend Turn " + str(3 - maxdepth))
    print(b)


    if b.is_game_over():
        return [-100, '']
    if maxdepth == 0:
        return [evalBoard(b), '']
    best = -100
    temp = [best, '']
    friend_moves = [move for move in b.legal_moves]
    for m in friend_moves:
        b.push(m)
        result = evalEnemyTurn(b, maxdepth - 1)
        b.pop()
        # print("If enemy plays ")
        # print(m)
        # print(" best value is "+str(result))
        print(result)
        if result[0] < best:
            best = result[0]
            temp = [best, m]
    # print("Best is "+str(best))
    if temp[1] == '':
        temp[1] = friend_moves[randint(0, len(friend_moves)-1)]
    return temp


board = chess.Board()

print(board)
print('\n')

turn = 0

while 1:
    if turn % 2 == 0:
        value = evalFriendTurn(board)
    else:
        value = evalEnemyTurn(board)
    print('-------------------')
    print(value)
    board.push(value[1])
    print(board)
    input('next turn ...')
    turn = turn + 1
    print('-------------------')

print(board)
# board.pop()
