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
    int trap(const vector<int> &hs) const;
};

int Solution::trap(const vector<int> &hs) const {
    if (hs.size() < 3)
        return 0;

    int res = 0;
    int left_max = 0;
    int right_max = 0;
    size_t l = 0;
    size_t r = hs.size() - 1;

    while (l <= r) {
        if (hs[l] < hs[r]) {
            if (hs[l] > left_max)
                left_max = hs[l];
            else
                res += left_max - hs[l];

            l++;
        } else {
            if (hs[r] > right_max)
                right_max = hs[r];
            else
                res += right_max - hs[r];

            r--;
        }
    }

    return res;
}

int main() {
    cout << Solution().trap({1, 0, 1}) << endl;
    // cout << Solution().trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
    // cout << Solution().trap({0, 5, 6, 4, 6, 1, 0, 0, 2, 7}) << endl;

    return 0;
}
