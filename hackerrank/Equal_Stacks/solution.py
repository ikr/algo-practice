#!/usr/bin/env python3


from collections import deque


def equalStacks(s1, s2, s3):
    ses = (s1, s2, s3)
    hes = list(map(sum, ses))
    if hes[0] == hes[1] == hes[2]:
        return hes[0]
    while hes[index_of_max(hes)] > 0:
        i = index_of_max(hes)
        c = ses[i].popleft()
        hes[i] -= c
        if hes[0] == hes[1] == hes[2]:
            return hes[0]
    return 0


def index_of_max(xs):
    return xs.index(max(xs))

if __name__ == '__main__':
    n1N2N3 = input().split()
    h1 = deque(map(int, input().rstrip().split()))
    h2 = deque(map(int, input().rstrip().split()))
    h3 = deque(map(int, input().rstrip().split()))
    result = equalStacks(h1, h2, h3)
    print(result)
