#include <bits/stdc++.h>

using namespace std;

using Iter = vector<int>::const_iterator;

int progressing_sum(const Iter first, const Iter last) {
    int multiplier = 1;
    int ans = 0;
    
    for (auto it = first; it != last; ++it) {
        ans += *it * multiplier;
        ++multiplier;
    }

    return ans;
}

struct Solution final {
    int maxSatisfaction(vector<int> xs) const {
        const int sz = xs.size();
        if (!sz) return 0;

        sort(xs.begin(), xs.end());
        int ans = 0;

        for (auto start = xs.cbegin(); start != xs.cend(); ++start) {
            ans = max(ans, progressing_sum(start, xs.cend()));
        }

        return ans;
    }
};

int main() {
    assert(Solution{}.maxSatisfaction({-1,-8,0,5,-9}) == 14);
    assert(Solution{}.maxSatisfaction({4,3,2}) == 20);
    assert(Solution{}.maxSatisfaction({-1,-4,-5}) == 0);
    assert(Solution{}.maxSatisfaction({-2,5,-1,0,3,-3}) == 35);

    return 0;
}
