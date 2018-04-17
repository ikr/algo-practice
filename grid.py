#!/usr/bin/env python3


class Solution:
    # @param A : integer
    # @return a list of list of integers
    def prettyPrint(self, A):
        d = 2 * A - 1
        grid = []
        for r in range(d):
            row = []
            for c in range(d):
                row.append(A)
            grid.append(row)
        for i in range(1, A):
            self.hline(grid, A - i, A - i, i * 2 - 1, i)
            self.hline(grid, A + i - 2, A - i, i * 2 - 1, i)
            self.vline(grid, A - i, A - i, i * 2 - 1, i)
            self.vline(grid, A - i, A + i - 2, i * 2 - 1, i)
        return grid

    def hline(self, grid, row, col, length, pen):
        for i in range(length):
            grid[row][col + i] = pen


    def vline(self, grid, row, col, length, pen):
        for i in range(length):
            grid[row + i][col] = pen


if __name__ == '__main__':
    s = Solution()
    rows = map(lambda r: ' '.join(map(str, r)), s.prettyPrint(5))
    print('\n'.join(rows))
