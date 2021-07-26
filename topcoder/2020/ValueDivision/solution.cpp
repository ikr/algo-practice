#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> gather_counts(const vector<int> &xs) {
	unordered_map<int, int> ans;
    
    for (const int x : xs) {
    	++ans[x];
    }
    
    return ans;
}

struct ValueDivision final {
    vector<int> getArray(vector<int> xs) const {
    	auto counts_by_x = gather_counts(xs);
        const int sz = xs.size();
        
        for (int i = 0; i < sz;) {
            if (xs[i] > 1 && counts_by_x[xs[i]] > 1) {
                --counts_by_x[xs[i]];
                --xs[i];
                ++counts_by_x[xs[i]];
                
                i = 0;
            } else {
                ++i;
            }
        }
        
    	return xs;
    }
};
