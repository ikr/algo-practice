#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace {
struct Coord {
    Coord(int row, int col) : r{row}, c{col} {}
    int row() const;
    int col() const;

  private:
    int r;
    int c;
};

struct Solution {
    void solveSudoku(vector<vector<char>> &rows) const;

  private:
    using Rows = vector<vector<char>>;
    static constexpr int bsize = 3;
    static constexpr int gsize = bsize * bsize;
    static const vector<char> digits;

    static bool search_recur(Rows &rows);
    static optional<Coord> first_absent_coord(const Rows &rows);
    static const vector<char> init_digits();
};

const vector<char> Solution::digits = Solution::init_digits();

void Solution::solveSudoku(Rows &rows) const {}

bool Solution::search_recur(Rows &rows) {
    optional<const Coord> v_coord = first_absent_coord(rows);

    if (!v_coord)
        return true;

    for (const char d : digits) {
        if (is_valid(rows, v_coord, d)) {
            rows[v_coord->row()][v_coord->col()] = d;

            if (search_recur(rows))
                return true;

            rows[v_coord->row()][v_coord->col()] = '.';
        }
    }

    return false;
}

optional<Coord> Solution::first_absent_coord(const Rows &rows) {
    for (int row = 0; row != gsize; ++row) {
        for (int col = 0; col != gsize; ++col) {
            if (rows[row][col] == '.')
                return {{row, col}};
        }
    }

    return nullopt;
}

const vector<char> Solution::init_digits() {
    vector<char> result(gsize);
    iota(result.begin(), result.end(), '1');
    return result;
}
} // namespace

vector<vector<char>> input1() {
    return {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
}

int main() {
    Solution s;

    cout << endl;

    return 0;
}
