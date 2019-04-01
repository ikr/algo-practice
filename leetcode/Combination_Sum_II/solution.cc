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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &rows) {
    for (auto row : rows) {
        os << row << endl;
    }

    return os;
}

using vec = vector<int>;
using vvec = vector<vector<int>>;

namespace {

void summands_recur(vec::const_iterator ixs, vec::const_iterator ixs_end,
                    const int target, vec &sprout, vvec &res) {
    if (!target) {
        res.push_back(sprout);
        return;
    }

    if (ixs != ixs_end) {
        summands_recur(ixs + 1, ixs_end, target, sprout, res);

        sprout.push_back(*ixs);
        summands_recur(ixs + 1, ixs_end, target - *ixs, sprout, res);
        sprout.pop_back();
    }
}

} // namespace

struct Solution {
    vvec combinationSum2(const vec &xs, const int target);
};

vvec Solution::combinationSum2(const vec &xs, const int target) {
    vvec result;
    vec sprout;
    summands_recur(xs.begin(), xs.end(), target, sprout, result);

    for (vec &solution : result) {
        sort(solution.begin(), solution.end());
    }

    sort(result.begin(), result.end());
    auto new_end = unique(result.begin(), result.end());
    result.erase(new_end, result.end());

    return result;
}

int main() {
    cout << Solution().combinationSum2({10, 1, 2, 7, 6, 1, 5}, 8) << endl;
    cout << Solution().combinationSum2({2, 5, 2, 1, 2}, 5) << endl;
    cout << Solution().combinationSum2({}, 5) << endl;

    cout << Solution().combinationSum2({10, 1,  2, 7, 6,  1, 5, 10, 1, 2,
                                        7,  6,  1, 5, 10, 1, 2, 7,  6, 1,
                                        5,  10, 1, 2, 7,  6, 1, 5,  10},
                                       8)
         << endl;

    cout << Solution().combinationSum2(
                {14, 6,  25, 9,  30, 20, 33, 34, 28, 30, 16, 12, 31, 9,
                 9,  12, 34, 16, 25, 32, 8,  7,  30, 12, 33, 20, 21, 29,
                 24, 17, 27, 34, 11, 17, 30, 6,  32, 21, 27, 17, 16, 8,
                 24, 12, 12, 28, 11, 33, 10, 32, 22, 13, 34, 18, 12},
                27)
         << endl;

    return 0;
}
