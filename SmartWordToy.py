from collections import deque
import resource

class SmartWordToy:
    def minPresses(self, start, finish, forbid):
        if (matches_any(forbid, finish)):
            return -1

        D = {}
        D[start] = 0
        Q = deque()
        Q.append(start)

        while len(Q) > 0:
            current = Q.popleft()

            for a in adjacent(forbid, current):
                if not a in D:
                    D[a] = D[current] + 1
                    if a == finish:
                        return D[a]
                    Q.append(a)

        return -1

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


forbid = ('ab bc cd ef', 'zgftyr zgfs qwertz zghjkl', 'az xy abcdef akgyuoqzx')
print(matches_any(forbid, 'aaaa'))
print(matches_any(forbid, 'ikrr'))

swt = SmartWordToy();
print(swt.minPresses('aaaa', 'ikrr', forbid))

print(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss / 1000)
