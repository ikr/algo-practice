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
    vector<vector<int>> combinationSum2(const vector<int> &xs,
                                        const int target);
};

vector<vector<int>> Solution::combinationSum2(const vector<int> &xs,
                                             const int target) {
    vector<vector<int>> result;
    summands_recur(xs, target, result);

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
