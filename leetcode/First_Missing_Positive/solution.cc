#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (T x : xs) {
        os << x << ' ';
    }

    return os;
}

namespace {

void place_oob(vector<int> &xs, const int x) {
    const int sz = static_cast<int>(xs.size());
    assert(x >= sz);

    if (xs[0] < sz) {
        xs[0] = x;
        return;
    }

    xs[0] = min(xs[0], x);
}

void place_recur(vector<int> &xs, const int stash) {
    assert(xs.size());
    assert(stash > 0);
    const int sz = static_cast<int>(xs.size());

    if (stash >= sz) {
        place_oob(xs, stash);
        return;
    }

    const size_t idx = static_cast<size_t>(stash);
    const int new_stash = xs[idx];
    xs[idx] = stash;

    if (new_stash <= 0 || new_stash == stash)
        return;

    place_recur(xs, new_stash);
}

} // namespace

struct Solution {
    int firstMissingPositive(vector<int> &xs);
};

int Solution::firstMissingPositive(vector<int> &xs) {
    assert(xs.size() < numeric_limits<int>::max());

    if (!xs.size())
        return 1;

    if (xs.size() == 1)
        return xs[0] == 1 ? 2 : 1;

    for (size_t i = 0; i != xs.size(); ++i) {
        if (xs[i] <= 0 || xs[i] == static_cast<int>(i))
            continue;

        place_recur(xs, xs[i]);
    }

    for (size_t i = 1; i != xs.size(); ++i) {
        const int ii = static_cast<int>(i);

        if (xs[i] != ii)
            return ii;
    }

    return xs[0] == xs.back() + 1 ? xs[0] + 1 : xs.back() + 1;
}

int main() {
    vector<int> xs{1, 2, 0};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {3, 4, -1, 1};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {7, 8, 9, 11, 12};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {3, 2, 1, 6, 5, 4, 7, 9, 9, 9, 9, 8, 11, 12, 11, 11};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {numeric_limits<int>::max()};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {2};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {1, 3};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {1, 2};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {2, 3};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {0, 1, 2, 3, 4, 5};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {12, 34, 41, 9,  14, 9,  26, 13, 13, 4,  19, 5,  19, 18,
          -1, 6,  5,  32, -9, 8,  35, -6, 41, -2, 11, 41, -6, 13,
          17, -8, 41, 34, -2, 40, 2,  24, 21, 36, 1,  22, 1,  3};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,
          14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,
          27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
          40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,
          53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,
          66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,
          79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,
          92,  93,  94,  95,  96,  97,  98,  99,  100, 101, 102, 103, 104,
          105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117,
          118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    return 0;
}
