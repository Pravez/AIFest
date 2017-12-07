from random import randint, getrandbits, choice
import numpy
from collections import namedtuple

__boardSize__ = 3


class Board:
    _data = None

    def __init__(self, copyFrom=None, randomize=False):
        if copyFrom is None:
            fromList = [x for x in range(0, __boardSize__**2)]
            if randomize:
                fromList = sorted(fromList, key=lambda x: getrandbits(1))
            self._data = numpy.reshape(
                fromList, (__boardSize__, __boardSize__))
        else:
            self._data = numpy.array(copyFrom, copy=True)

    def empty(self):
        p = numpy.where(self._data == 0)
        return (p[0][0], p[1][0])

    def _inBound(self, x):
        return x >= 0 and x < __boardSize__

    def randomMove(self):
        p = self.empty()
        assert self._data[p[0], p[1]] == 0
        move = choice([(-1, 0), (+1, 0), (0, -1), (0, +1)])
        if self._inBound(move[0] + p[0]) and self._inBound(move[1] + p[1]):
            self._data[p[0], p[1]] = self._data[p[0] + move[0], p[1] + move[1]]
            self._data[p[0] + move[0], p[1] + move[1]] = 0

    def next(self):
        toret = []
        e = self.empty()
        for x, y in ((-1, 0), (+1, 0), (0, -1), (0, +1)):
            if self._inBound(x + e[0]) and self._inBound(y + e[1]):
                n = Board(copyFrom=self._data)
                n._data[e[0], e[1]] = n._data[x + e[0], y + e[1]]
                n._data[x + e[0], y + e[1]] = 0
                toret.append(n)
        return toret

    def __eq__(self, other):
        return numpy.array_equal(self._data, other._data)

    def __hash__(self):
        self._data.flags.writeable = False
        h = hash(self._data.data.tobytes())
        self._data.flags.writeable = True
        return h

    def calcH(self):
        global boardGoal  # Humm this is ugly (embarrassing)
        total = 0
        for (x, y), v in numpy.ndenumerate(self._data):
            if boardGoal._data[x, y] != v:
                total += 1
        return total


class Node:
    state = None
    father = None
    g = 0
    f = 0

    def __init__(self, state, father=None, g=0, f=0):
        self.state = state
        self.father = father
        self.g = g
        self.f = f

    def sameAsState(self, state):
        return (state is self.state) or (numpy.array_equal(self.state._data, state._data))


class Frontiere:
    _nodes = None

    def __init__(self):
        self._nodes = []

    # Very costly Frontiere functions
    def getNext(self):
        assert self._nodes is not []
        bestValue = None
        bestNode = None
        for n in self._nodes:
            if bestValue is None or n.f < bestValue:
                bestValue = n.f
                bestNode = n
        if bestNode is not None:
            self._nodes.remove(bestNode)
        return bestNode

    def getNodeByState(self, state):
        for n in self._nodes:
            if n.sameAsState(state):
                return n
        return None

    def addNode(self, state, father=None, g=0, checkAlreadyThere=False):
        if checkAlreadyThere:
            n = self.getNodeByState(state)
            self._nodes.remove(n)
        self._nodes.append(Node(state, father, g, g + state.calcH()))

    def __len__(self):
        return len(self._nodes)

    def size(self):
        return len(self._nodes)


frontiere = Frontiere()
closed = set()  # Dictionary of seen boards

boardGoal = Board(randomize=False)
boardInit = Board(randomize=False)
for i in range(0, 30):
    boardInit.randomMove()

print("Initial Node: ")
print(boardInit._data)
frontiere.addNode(boardInit)
found = False
iterations = 0

while frontiere.size() > 0 and not found:
    n = frontiere.getNext()
    if n.sameAsState(boardGoal):
        found = True
        break

    for nn in n.state.next():
        if nn not in closed:
            previous = frontiere.getNodeByState(nn)
            if previous is None:
                frontiere.addNode(nn, n, n.g + 1)
            elif previous.g > n.g:
                previous.valid = False
                frontiere.addNode(nn, n, n.g + 1)
    closed.add(n)
    iterations += 1

print("Solution of cost ", n.g, " found in ", iterations,
      " steps and ", len(closed) + len(frontiere), " created nodes:")
noeudCourant = n
solution = []
while noeudCourant is not None:
    solution.append(noeudCourant.state)
    noeudCourant = noeudCourant.father

while len(solution) > 0:
    print(solution.pop()._data)
