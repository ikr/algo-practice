#include <algorithm>
#include <bitset>
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

struct Coord {
    Coord(int row, int col) : r{row}, c{col} {}

    int row() const { return r; }
    int col() const { return c; }

    Coord next_row() const { return {r + 1, c}; }
    Coord next_col() const { return {r, c + 1}; }

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
    static bool is_valid(const Rows &rows, const Coord &coord, const char x);
    static vector<Coord> row_coords(const Coord &x);
    static vector<Coord> col_coords(const Coord &x);
    static vector<Coord> box_coords(const Coord &x);
    static unordered_set<char> elements_set(const Rows &rows,
                                            const vector<Coord> &coords);
    static optional<Coord> first_absent_coord(const Rows &rows);
    static vector<char> init_digits();
};

const vector<char> Solution::digits = Solution::init_digits();

void Solution::solveSudoku(Rows &rows) const { search_recur(rows); }

bool Solution::search_recur(Rows &rows) {
    optional<const Coord> v_coord = first_absent_coord(rows);

    if (!v_coord)
        return true;

    for (const char d : digits) {
        if (is_valid(rows, *v_coord, d)) {
            rows[v_coord->row()][v_coord->col()] = d;

            if (search_recur(rows))
                return true;

            rows[v_coord->row()][v_coord->col()] = '.';
        }
    }

    return false;
}

bool Solution::is_valid(const Rows &rows, const Coord &coord, char x) {
    if (elements_set(rows, row_coords(coord)).count(x))
        return false;

    if (elements_set(rows, col_coords(coord)).count(x))
        return false;

    if (elements_set(rows, box_coords(coord)).count(x))
        return false;

    return true;
}

vector<Coord> Solution::row_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        result.push_back({x.row(), i});
    }

    return result;
}

vector<Coord> Solution::col_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        result.push_back({i, x.col()});
    }

    return result;
}

vector<Coord> Solution::box_coords(const Coord &x) {
    const Coord o = {bsize * (x.row() / bsize), bsize * (x.col() / bsize)};
    const Coord o1 = o.next_row();
    const Coord o2 = o1.next_row();

    return {o,  o.next_col(),  o.next_col().next_col(),
            o1, o1.next_col(), o1.next_col().next_col(),
            o2, o2.next_col(), o2.next_col().next_col()};
}

unordered_set<char> Solution::elements_set(const Rows &rows,
                                           const vector<Coord> &coords) {
    unordered_set<char> result;

    for (const Coord &x : coords)
        if (rows[x.row()][x.col()] != '.')
            result.insert(rows[x.row()][x.col()]);

    return result;
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

vector<char> Solution::init_digits() {
    vector<char> result(gsize);
    iota(result.begin(), result.end(), '1');
    return result;
}

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

vector<vector<char>> input2() {
    return {{'.', '.', '.', '.', '.', '7', '.', '.', '9'},
            {'.', '4', '.', '.', '8', '1', '2', '.', '.'},
            {'.', '.', '.', '9', '.', '.', '.', '1', '.'},
            {'.', '.', '5', '3', '.', '.', '.', '7', '2'},
            {'2', '9', '3', '.', '.', '.', '.', '5', '.'},
            {'.', '.', '.', '.', '.', '5', '3', '.', '.'},
            {'8', '.', '.', '.', '2', '3', '.', '.', '.'},
            {'7', '.', '.', '.', '5', '.', '.', '4', '.'},
            {'5', '3', '1', '.', '7', '.', '.', '.', '.'}};
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (T x : xs) {
        os << x << ' ';
    }

    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &rows) {
    for (auto row : rows) {
        os << row << endl;
    }

    return os;
}

int main() {
    auto rows = input1();
    cout << rows << endl;

    Solution().solveSudoku(rows);
    cout << rows << endl;

    rows = input2();
    cout << rows << endl;

    Solution().solveSudoku(rows);
    cout << rows << endl;

    return 0;
}
