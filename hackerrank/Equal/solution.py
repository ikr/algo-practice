#!/usr/bin/env python3


def equal(arr):
    trials = map(lambda x: equal_vary_target(arr, x), (0, 1, 2))
    return min(trials)


def equal_vary_target(arr, delta):
    m = min(arr)
    target = m - delta
    ops = 0 if delta == 0 else arr.count(m)
    for x in arr:
        if x == m:
            continue
        for y in (5, 2, 1):
            c = count_subtractions(x, y, target)
            if c > 0:
                x -= c * y
                ops += c
    return ops


def count_subtractions(from_x, of_ys, lower_bound):
    return (from_x - lower_bound) // of_ys


if __name__ == "__main__":
    t = int(input().strip())
    for a0 in range(t):
        n = int(input().strip())
        arr = list(map(int, input().strip().split(' ')))
        result = equal(arr)
        print(result)
