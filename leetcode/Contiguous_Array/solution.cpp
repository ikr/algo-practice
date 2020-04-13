#include <bits/stdc++.h>

using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

struct Solution final {
    int findMaxLength(const vector<int> &xs) const {
        const int sz = xs.size();
        vector<pair<int, int>> counts(sz + 1, {0, 0});
        
        int nots = 0, ones = 0;
        for (int i = 1; i <= sz; ++i) {
            if (xs[i - 1]) ++ones;
            else ++nots;
            
            counts[i] = {nots, ones};
        }
        
        int ans = 0;
        
        for (int i = 0; i <= sz - 1; ++i) {
            for (int j = i + 1; j <= sz; ++j) {
                const auto [lnots, lones] = counts.at(i);
                const auto [rnots, rones] = counts.at(j);
                
                if (rnots - lnots == rones - lones) {
                    ans = max(ans, j - i);
                }
            }
        }
        
        return ans;
    }
};

int main() {
    const int ans = Solution{}.findMaxLength({1,0,0,0,0,1,1,1,0,1,1,0,0,0});
    
    cout << "Answer is " << ans << endl;

    return 0;
}
