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

vec tail_excluding(const vec &xs, vec::const_iterator i) {
    ++i;

    vec res;
    copy(i, xs.end(), back_inserter(res));
    return res;
}

void summands_recur(const vec &xs, const int target, vec &sprout, vvec &res) {
    if (!target) {
        res.push_back(sprout);
        return;
    }

    if (!xs.size() || target < 0)
        return;

    for (auto i = xs.begin(); i != xs.end(); ++i) {
        vec ys = tail_excluding(xs, i);

        summands_recur(ys, target, sprout, res);

        if (*i <= target) {
            sprout.push_back(*i);
            summands_recur(ys, target - *i, sprout, res);
            sprout.pop_back();
        }
    }
}

} // namespace

struct Solution {
    vvec combinationSum2(const vec &xs, const int target);
};

vvec Solution::combinationSum2(const vec &xs, const int target) {
    vvec result;
    vec sprout;
    summands_recur(xs, target, sprout, result);

    for (auto &ys : result) {
        sort(ys.begin(), ys.end());
    }

    sort(result.begin(), result.end());
    unique(result.begin(), result.end());
    return result;
}

int main() {
    cout << Solution().combinationSum2({10, 1, 2, 7, 6, 1, 5}, 8) << endl;

    return 0;
}
