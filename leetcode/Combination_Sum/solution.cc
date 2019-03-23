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
                            const int target, const vector<int> &cand,
                            const int cand_sum, vector<vector<int>> &result);

    template <typename T>
    static std::vector<T> augmented(std::vector<T> xs, const T x) {
        xs.push_back(x);
        return xs;
    }
};

vector<vector<int>> Solution::combinationSum(const vector<int> &denoms,
                                             const int target) {
    vector<vector<int>> result;

    enum_change(denoms, denoms.size(), target, vector<int>{}, 0, result);

    return result;
}

void Solution::enum_change(const vector<int> &denoms, const size_t dused,
                           const int target, const vector<int> &cand,
                           const int cand_sum, vector<vector<int>> &result) {
    if (target == 0) {
        result.push_back(cand);
        return;
    }

    if (target < 0 || !dused)
        return;

    const int d = denoms[dused - 1];
    enum_change(denoms, dused, target - d, augmented(cand, d), cand_sum + d,
                result);

    enum_change(denoms, dused - 1, target, cand, cand_sum, result);
}

int main() {
    cout << Solution().combinationSum({2, 3, 5}, 8) << endl;

    return 0;
}
