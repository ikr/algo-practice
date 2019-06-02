#include "lest.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using RowCol = pair<size_t, size_t>;
using Matrix = vector<vector<int>>;

RowCol operator+(const RowCol &x, const RowCol &y) {
    return make_pair(x.first + y.first, x.second + y.second);
}

RowCol operator-(const RowCol &x, const RowCol &y) {
    assert(x.first >= y.first);
    assert(x.second >= y.second);
    return make_pair(x.first - y.first, x.second - y.second);
}

int &pixel(Matrix &matrix, const RowCol &row_col) {
    return matrix[row_col.first][row_col.second];
}

size_t layer_size(const size_t sz, const size_t depth) {
    return sz - 2 * depth;
}

RowCol layer_top_left(const size_t depth) { return make_pair(depth, depth); }

RowCol layer_top_right(const size_t sz, const size_t depth) {
    return make_pair(depth, sz - depth - 1);
}

RowCol layer_bottom_right(const size_t sz, const size_t depth) {
    return make_pair(sz - depth - 1, sz - depth - 1);
}

RowCol layer_bottom_left(const size_t sz, const size_t depth) {
    return make_pair(sz - depth - 1, depth);
}

void rotate_layer(Matrix &matrix, const size_t depth) {
    const size_t sz = matrix.size();

    for (size_t i = 0; i != layer_size(sz, depth) - 1; ++i) {
        const RowCol a{layer_top_left(depth) + make_pair(0, i)};
        const RowCol k{layer_top_right(sz, depth) + make_pair(i, 0)};
        const RowCol p{layer_bottom_right(sz, depth) - make_pair(0, i)};
        const RowCol x{layer_bottom_left(sz, depth) - make_pair(i, 0)};

        swap(pixel(matrix, a), pixel(matrix, k));
        swap(pixel(matrix, a), pixel(matrix, p));
        swap(pixel(matrix, a), pixel(matrix, x));
    }
}

struct Solution {
    void rotate(Matrix &matrix) {
        const size_t sz = matrix.size();

        for (size_t depth = 0; depth != sz / 2; ++depth) {
            rotate_layer(matrix, depth);
        }
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("3 x 3") {
        Matrix actual{
            {1,2,3},
            {4,5,6},
            {7,8,9},
        };

        Solution().rotate(actual);

        const Matrix expected{
            {7,4,1},
            {8,5,2},
            {9,6,3}
        };

        EXPECT(actual == expected);
    },
    CASE("4 x 4") {
        Matrix actual{
            { 5, 1, 9,11},
            { 2, 4, 8,10},
            {13, 3, 6, 7},
            {15,14,12,16}
        };

        Solution().rotate(actual);

        const Matrix expected{
            {15,13, 2, 5},
            {14, 3, 4, 1},
            {12, 6, 8, 9},
            {16, 7,10,11}
        };

        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
