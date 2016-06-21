class SmartWordToy:
    def minPresses(self, start, finish, forbid):
        return 0


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

print(char_neighbours('z'))
