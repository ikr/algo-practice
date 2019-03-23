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

struct Solution {
    vector<vector<int>> combinationSum(const vector<int> &denoms,
                                       const int target);

  private:
    static void enum_change(const vector<int> &denoms, const size_t dused,
                            const int target, vector<int> &cand,
                            const int cand_sum, vector<vector<int>> &result);
};

vector<vector<int>> Solution::combinationSum(const vector<int> &denoms,
                                             const int target) {
    vector<vector<int>> result;
    vector<int> cand;

    enum_change(denoms, denoms.size(), target, cand, 0, result);

    sort(result.begin(), result.end());
    return result;
}

void Solution::enum_change(const vector<int> &denoms, const size_t dused,
                           const int target, vector<int> &cand,
                           const int cand_sum, vector<vector<int>> &result) {
    if (target == 0) {
        result.push_back(cand);
        return;
    }

    if (target < 0 || !dused)
        return;

    const int d = denoms[dused - 1];
    cand.insert(cand.begin(), d);
    enum_change(denoms, dused, target - d, cand, cand_sum + d, result);

    cand.erase(cand.begin());
    enum_change(denoms, dused - 1, target, cand, cand_sum, result);
}

int main() {
    cout << Solution().combinationSum({5, 10, 20, 50}, 100) << endl;

    return 0;
}
