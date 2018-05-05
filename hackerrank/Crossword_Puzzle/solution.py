#!/usr/bin/env python3


import fileinput
from itertools import groupby, repeat, permutations


def crosswordPuzzle(crossword, hints):
    ws_by_l = groupby(sorted(hints.split(';'), key=len), len)
    wps_horz = word_placings(crossword, (0, 1))
    wps_vert = word_placings(transpose(crossword), (1, 0))
    wps_by_l = groupby(sorted(wps_horz + wps_vert, key=len), len)
    words_and_placings = []
    for iw, iwp in zip(ws_by_l, wps_by_l):
        words = list(iw[1])
        placings = list(iwp[1])
        words_and_placings.append((words, placings))
    solution = solve(words_and_placings)
    return print_crossword(solution)


def solve(words_and_placings):
    candidates = []
    enumerate_candidates(candidates, [], words_and_placings)
    for c in candidates:
        if is_solution(c):
            return c


def enumerate_candidates(memo, prefix, words_and_placings):
    if not words_and_placings:
        memo.append(prefix)
        return
    ws, ps = words_and_placings[0]
    for subcs in enumerate_subcandidates(ws, ps):
        new_prefix = prefix[:]
        new_prefix += subcs
        enumerate_candidates(memo, new_prefix, words_and_placings[1:])


def enumerate_subcandidates(words, placings):
    result = []
    for ws in permutations(words):
        current = []
        for i in range(len(ws)):
            current.append((ws[i], placings[i]))
        result.append(current)
    return result


def is_solution(candidate):
    letter_by_place = {}
    for w, p in candidate:
        for i in range(len(w)):
            if p[i] in letter_by_place and letter_by_place[p[i]] != w[i]:
                return False
            if p[i] not in letter_by_place:
                letter_by_place[p[i]] = w[i]
    return True


def print_crossword(solution):
    grid = []
    for i in range(10):
        grid.append(list(repeat('+', 10)))
    for word, placing in solution:
        for i in range(len(word)):
            row, col = placing[i]
            grid[row][col] = word[i]
    return map(lambda x: ''.join(x), grid)


def word_placings(lines, places_delta):
    result = []
    for i in range(len(lines)):
        origin = (i, 0) if places_delta[1] == 1 else (0, i)
        wps = word_placings_from_line(lines[i], origin, places_delta)
        if wps:
            result += wps
    return tuple(result)


def word_placings_from_line(line, origin_place, places_delta):
    result = []
    current = []
    for i in range(len(line)):
        if line[i] == '-':
            dr, dc = map(lambda x: x * i, places_delta)
            current.append((origin_place[0] + dr, origin_place[1] + dc))
        else:
            if len(current) > 1:
                result.append(tuple(current))
            current = []
    if len(current) > 1:
        result.append(tuple(current))
    return tuple(result)


def transpose(lines):
    return tuple(''.join(line[i] for line in lines) for i in range(len(lines[0])))


if __name__ == '__main__':
    crossword = []
    hints = ''
    for line in fileinput.input():
       if len(crossword) < 10:
           crossword.append(line.strip())
       else:
           hints = line.strip()
    result = crosswordPuzzle(crossword, hints)
    print('\n'.join(map(str, result)))
