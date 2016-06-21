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


print(matches_any(('lf a tc a', 'a b c d'), 'fate'))
