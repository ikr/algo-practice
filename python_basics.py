from functools import reduce

def sum (xs):
    return reduce(lambda x, y: x + y, xs, 0);

print(sum((1, 1, 1, 2, 2)))
