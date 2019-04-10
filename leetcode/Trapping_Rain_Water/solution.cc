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
    const size_t sz{hs.size()};

    if (sz < 3)
        return 0;

    size_t l{0}, r{sz - 1};
    int lmax{0}, rmax{0}, res{0};

    for (;;) {
        if (l == r) {
            const int vol = min(lmax, rmax) - hs[l];
            if (vol > 0) res += vol;
            break;
        }

        if (hs[l] < hs[r]) {
            if (hs[l] > lmax)
                lmax = hs[l];
            else
                res += lmax - hs[l];

            ++l;
        } else {
            if (hs[r] > rmax)
                rmax = hs[r];
            else
                res += rmax - hs[r];

            --r;
        }
    }

    return res;
}

int main() {
    cout << Solution().trap({1, 0, 1}) << endl;
    cout << Solution().trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
    cout << Solution().trap({0, 5, 6, 4, 6, 1, 0, 0, 2, 7}) << endl;

    return 0;
}
