from itertools import repeat
from math import sqrt

def turns_count(x, y):
    return int(sqrt(x + y))

def next_seq(wins):
    if 'A' not in wins:
        return ''
    result = list(wins)
    for i in range(len(wins)):
        if result[i] == 'A':
            result[i] = 'K'
            break
        result[i] = 'A'
    return ''.join(result)

def scores(seq):
    x = 0
    y = 0
    for i in range(len(seq)):
        if seq[i] == 'A':
            x += 2 * i + 1
        else:
            y += 2 * i + 1
    return x, y

def min_alice_wins(a_score, k_score):
    if a_score == 0 and k_score == 0:
        return 0
    sz = turns_count(a_score, k_score)
    seq = ''.join(repeat('A', sz))
    min_a_turns = float('inf')
    while seq:
        x, y = scores(seq)
        if x == a_score and y == k_score and seq.count('A') < min_a_turns:
            min_a_turns = seq.count('A')
        seq = next_seq(seq)
    return min_a_turns if min_a_turns < float('inf') else -1

class AliceGame:
    def findMinimumValue(self, x, y):
        return min_alice_wins(x, y)

if __name__ == '__main__':
    print(min_alice_wins(0, 0))
