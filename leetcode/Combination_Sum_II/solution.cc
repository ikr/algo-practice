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

struct Solution {
    using vvec = vector<vector<int>>;

    vvec combinationSum2(const vector<int> &xs, const int target);
};

Solution::vvec Solution::combinationSum2(const vector<int> &xs,
                                         const int target) {
    vvec result;
    vector<int> sprout;
    summands_recur(xs, target, sprout, result);

    for (auto &ys : result) {
        sort(ys.begin(), ys.end());
    }

    sort(result.begin(), result.end());
    unique(result.begin(), result.end());
    return result;
}

int main() {
    cout << 42 << endl;

    return 0;
}
