from itertools import product
from collections import deque

class SmartWordToy:
    def minPresses(self, start, finish, forbid):
        if (matches_any(forbid, finish)):
            return -1

        G = init_graph(forbid)
        G[start]['d'] = 0
        Q = deque()
        Q.append(start)

        while len(Q) > 0:
            current = Q.popleft()

            for a in G[current]['a']:
                if G[a]['d'] < 0:
                    G[a]['d'] = G[current]['d'] + 1
                    Q.append(a)

        return G[finish]['d']


def init_graph(forbid):
    result = {}

    for vertexTuple in product(az(), az(), az(), az()):
        vertexWord = ''.join(vertexTuple)

        if not matches_any(forbid, vertexWord):
            result[vertexWord] = {'a': adjacent(forbid, vertexWord), 'd': -1}

    return result

def az():
    return ''.join(tuple(map(chr, range(ord('a'), ord('z') + 1))))

def adjacent(forbid, word):
    def is_allowed(x):
        return not matches_any(forbid, x)

    return tuple(filter(is_allowed, adjacent_unconstrained(word)))


def adjacent_unconstrained(word):
    result = []

    for index in range(len(word)):
        prefix = word[0 : index]
        suffix = word [index + 1 :]

        for n in char_neighbours(word[index]):
            result.append(prefix + n + suffix)

    return tuple(result)


def matches_any(constraints, word):
    for c in constraints:
        if matches(c, word):
            return True

    return False


def matches(constraint, word):
    for index, item in enumerate(constraint.split(' ')):
        if not word[index] in item:
            return False

    return True


def char_neighbours(c):
    lo = chr(ord(c) - 1) if c != 'a' else 'z'
    hi = chr(ord(c) + 1) if c != 'z' else 'a'
    return lo, hi
