#!/usr/bin/env python3


def countArray(n, k, x):
    S1 = S1_ = k - 1
    S2 = S2_ = k - 2
    for i in range(4, n + 1):
        S1_ = ((k - 1) * S2) % (10 ** 9 + 7)
        S2_ = (S1 + (k - 2) * S2) % (10 ** 9 + 7)
        S1 = S1_
        S2 = S2_

    return S1_ if x == 1 else S2_



if __name__ == "__main__":
    n, k, x = input().strip().split(' ')
    n, k, x = [int(n), int(k), int(x)]
    answer = countArray(n, k, x)
    print(answer)
