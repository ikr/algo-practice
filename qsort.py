#!/usr/bin/env python3


def partition(xs, l, r):
    print(xs)
    p = l
    for i in range(l + 1, r + 1):
        if xs[i] < xs[p]:
            swap(xs, p, p + 1)
            if i > p + 1:
                swap(xs, p, i)
            p = p + 1
    print(xs, p)
    print()
    return p

def swap(xs, i, j):
    xs[i], xs[j] = xs[j], xs[i]

partition([42, -1], 0, 1)
partition([2, 4, 1, -7, 6, 1, 4], 0, 6)

l = [9, 0, -5, 6, 29, 17, 3, 6, 8, 9, 13, 4, 24, 33, 22, 23, 45, 9]
partition(l, 0, len(l) - 1)
