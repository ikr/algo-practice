#include <bits/stdc++.h>

using namespace std;

using Lng = long long;

vector<pair<int, int>> gather_disjoint_ranges(const string &s, const string &r) {
    vector<pair<int, int>> ans;
    
    int first_diff_index = -1;
    for (int i = 0; i != s.size(); ++i) {
        if (s[i] == r[i]) {
            if (first_diff_index >= 0) {
                ans.emplace_back(first_diff_index, i - 1);
                first_diff_index = -1;
            }
        } else {
            if (first_diff_index < 0) {
                first_diff_index = i;   
            }
        }
    }
    
    if (first_diff_index >= 0) ans.emplace_back(first_diff_index, s.size() - 1);
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    int t;
    cin >> t;
    
    for (int tc = 0; tc < t; ++tc) {
        string s, r;
        cin >> s >> r;
        
        const auto drs = gather_disjoint_ranges(s, r);
        
        if (!drs.empty()) { 
            pair<int, int> last_range = drs[0];
            Lng ops_count = drs.size();
            
            Lng letters_count = accumulate(drs.cbegin(), drs.cend(), 0LL, [](const Lng memo, const auto ab) { 
                return memo + ab.second - ab.first + 1; 
            });
            
            Lng ans = ops_count * letters_count;
            
            for (int i = 1; i < drs.size(); ++i) {
                const auto [a, b] = last_range;
                const auto [c, d] = drs[i];
                
                letters_count += (c - b - 1);
                last_range = {a, d};
                --ops_count;
                
                ans = min(ans, ops_count * letters_count);
            }
            
            cout << ans << endl;
        } else {
            cout << 0 << endl;
        }
    }
    
    return 0;
}
