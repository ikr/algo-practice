from itertools import repeat
from math import sqrt

def turns_count(x, y):
    return int(sqrt(x + y))

def next_seq_scores_a_turns(n, seq, x, y, a_turns):
    if x == 0:
        return '', x, y, a_turns
    for i in range(n):
        d = 2 * i + 1
        if seq[i] == 'A':
            seq[i] = 'K'
            x -= d
            y += d
            a_turns -= 1
            break
        x += d
        y -= d
        a_turns += 1
        seq[i] = 'A'
    return seq, x, y, a_turns

def min_alice_wins(a_score, k_score):
    if a_score == 0 and k_score == 0:
        return 0
    sz = turns_count(a_score, k_score)
    seq = list(repeat('A', sz))
    x = sz * sz
    y = 0
    a_turns = sz
    min_a_turns = float('inf')
    while seq:
        if x == a_score and y == k_score and a_turns < min_a_turns:
            min_a_turns = a_turns
        seq, x, y, a_turns = next_seq_scores_a_turns(sz, seq, x, y, a_turns)
    return min_a_turns if min_a_turns < float('inf') else -1

class AliceGame:
    def findMinimumValue(self, x, y):
        return min_alice_wins(x, y)

if __name__ == '__main__':
    print(min_alice_wins(300, 325))
