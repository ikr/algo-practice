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

class RepeatReg {
  public:
    RepeatReg() : xs{}, repeated{false} {}

    void register_element(char x) {
        if (x == '.')
            return;

        if (xs.count(x)) {
            repeated = true;
            return;
        }

        xs.insert(x);
    }

    bool has_repeats() const { return repeated; }

  private:
    unordered_set<char> xs;
    bool repeated;
};

class Solution {
  public:
    bool isValidSudoku(const vector<vector<char>> &rows) const {
        return confirm_correct(rows);
    }

  private:
    static bool confirm_correct(const vector<vector<char>> &rows) {
        const int sz = box_size * box_size;

        for (int ent = 0; ent != sz; ++ent) {
            RepeatReg rrow{}, rcol{}, rbox{};

            for (int idx = 0; idx != sz; ++idx) {
                rrow.register_element(rows[ent][idx]);
                rcol.register_element(rows[idx][ent]);
                rbox.register_element(box_element(rows, ent, idx));
            }

            if (rrow.has_repeats() || rcol.has_repeats() || rbox.has_repeats())
                return false;
        }

        return true;
    }

    static char box_element(const vector<vector<char>> &rows, int ent,
                            int idx) {
        const auto bcoord = box_coord(ent);
        const int org_row = bcoord.first * box_size;
        const int org_col = bcoord.second * box_size;

        const auto ecoord = box_coord(idx);
        return rows[org_row + ecoord.first][org_col + ecoord.second];
    }

    static pair<int, int> box_coord(int box_idx) {
        return {box_idx / box_size, box_idx % box_size};
    }

    static constexpr int box_size = 3;
};

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
    auto result = input1();
    result[0][0] = '8';
    return result;
}

int main() {
    Solution s;

    cout << s.isValidSudoku(input1()) << endl;
    cout << s.isValidSudoku(input2()) << endl;

    return 0;
}
