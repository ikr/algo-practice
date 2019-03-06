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

class Solution {
    using Rows = vector<vector<char>>;

  public:
    void solveSudoku(vector<vector<char>> &rows) const;

  private:
    static bool search_recur(Rows &rows);
};

void Solution::solveSudoku(vector<vector<char>> &rows) const {}

bool Solution::search_recur(Rows &rows) {
    optional<const Coord> v_coord = first_absent_coord(rows);

    if (!v_coord)
        return true;

    for (const char d : digits()) {
        if (is_valid(rows, v_coord, d)) {
            rows[v_coord.row()][v_coord.col()] = d;

            if (search_recur(rows))
                return true;

            rows[v_coord.row()][v_coord.col()] = '.';
        }
    }

    return false;
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

int main() {
    Solution s;

    cout << endl;

    return 0;
}
