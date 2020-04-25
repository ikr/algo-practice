#include <bits/stdc++.h>

using namespace std;

pair<int, int> count_left_right(const string &s) {
	pair<int, int> ans{0, 0};
    
    for (const char c : s) {
    	if (c == '(') ++ans.first;
        else if (c == ')') ++ans.second;
    }
    
    return ans;
}

int count_beauty(const int pairs_count) {
    assert(pairs_count >= 0);
    if (pairs_count < 2) return pairs_count;
    return count_beauty(pairs_count - 1) + pairs_count;
}

template <typename T> T min_of(const pair<T, T> &p) {
    return min(p.first, p.second);
}

struct MaximumBalances final {
	 int solve(const string &s) const {
         return count_beauty(min_of(count_left_right(s)));
     }
};
