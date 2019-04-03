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

namespace {

int place_x(vector<int> &xs, const int index) {
    assert(index >= 0);
    const int x = xs[index];

    int res = -1;

    if (x >= 0) {
        res = xs[x];
        xs[x] = x;
    }

    return res;
}

void place_chain(vector<int> &xs, const int start_index) {
    assert(start_index >= 0 && start_index < static_cast<int>(xs.size()));
    int i = start_index;

    while (i >= 0 && xs[i] > 0) {
        i = place_x(xs, i);
    }
}

} // namespace

struct Solution {
    int firstMissingPositive(vector<int> &xs);
};

int Solution::firstMissingPositive(vector<int> &xs) {
    assert(xs.size());

    const int max_x = *max(xs.begin(), xs.end());

    return max_x + 1;
}

int main() {
    vector<int> xs{1, 2, 0};
    cout << Solution().firstMissingPositive(xs) << endl;

    xs = {3, 4, -1, 1};
    cout << Solution().firstMissingPositive(xs) << endl;

    xs = {7, 8, 9, 11, 12};
    cout << Solution().firstMissingPositive(xs) << endl;

    return 0;
}
