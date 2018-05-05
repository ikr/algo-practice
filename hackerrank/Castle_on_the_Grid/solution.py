#!/usr/bin/env python3

from collections import deque


def minimumMoves(grid, start_row, start_col, goal_row, goal_col):
    if (start_row, start_col) == (goal_row, goal_col):
        return 0

    to_visit = deque([(start_row, start_col)])
    distances = {(start_row, start_col): 0}

    while to_visit:
        current = to_visit.popleft()
        for a in all_adjacent(grid, current):
            if not a in distances:
                distances[a] = distances[current] + 1

                if a == (goal_row, goal_col):
                    return distances[a]

                to_visit.append(a)

    return -1


def all_adjacent(grid, vertex):
    size = len(grid)
    row, col = vertex

    for av in adjecency_vectors():
        d = 1
        while True:
            r = row + d * av[0]
            c = col + d * av[1]

            if 0 <= r < size and 0 <= c < size and grid[r][c] == '.':
                yield((r, c))
                d += 1
            else:
                break


def adjecency_vectors():
    return ((-1, 0), (0, 1), (1, 0), (0, -1))


if __name__ == "__main__":
    n = int(input().strip())

    grid = []
    while n > 0:
        grid.append(tuple(input().strip()))
        n -= 1

    start_row, start_col, goal_row, goal_col = map(int, input().strip().split(' '))
    print(minimumMoves(grid, start_row, start_col, goal_row, goal_col))
