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
    if (ixs == ixs_end)
        return;

    if (!target) {
        res.push_back(sprout);
        return;
    }

    summands_recur(ixs + 1, ixs_end, target, sprout, res);

    sprout.push_back(*ixs);
    summands_recur(ixs + 1, ixs_end, target - *ixs, sprout, res);
    sprout.pop_back();
}

} // namespace

struct Solution {
    vvec combinationSum2(const vec &xs, const int target);
};

vvec Solution::combinationSum2(const vec &xs, const int target) {
    vvec result;
    vec sprout;
    summands_recur(xs.begin(), xs.end(), target, sprout, result);
    return result;
}

int main() {
    cout << Solution().combinationSum2({10, 1, 2, 7, 6, 1, 5}, 8) << endl;

    return 0;
}
