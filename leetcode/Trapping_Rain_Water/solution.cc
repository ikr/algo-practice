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
    int trap(const vector<int> &hs);
};

int Solution::trap(const vector<int> &hs) {
    if (hs.size() < 3)
        return 0;

    int res = 0;
    int left_max = hs[0];
    int right_max = hs.back();
    size_t l = 0;
    size_t r = hs.size() - 1;

    for (;;) {
        if (l > r)
            break;

        if (l == r) {
            const int vol = min(left_max, right_max) - hs[l];

            if (vol > 0)
                res += vol;

            break;
        }

        const int lvol = min(left_max, max(hs[r], right_max)) - hs[l];
        const int rvol = min(max(left_max, hs[l]), right_max) - hs[r];

        if (lvol > 0)
            res += lvol;

        if (rvol > 0)
            res += rvol;

        left_max = max(left_max, hs[l]);
        right_max = max(hs[r], right_max);

        ++l;
        --r;
    }

    return res;
}

int main() {
    cout << Solution().trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;

    return 0;
}
