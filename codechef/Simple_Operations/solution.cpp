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
    int t;
    cin >> t;
    
    for (int tc = 0; tc < t; ++tc) {
        string s, r;
        cin >> s >> r;
        
        const auto drs = gather_disjoint_ranges(s, r);
        
        if (!drs.empty()) { 
            pair<int, int> last_range = drs[0];
            int ops_count = 1;
            int letters_count = last_range.second - last_range.first + 1;
            
            for (int i = 1; i < drs.size(); ++i) {
                const auto [a, b] = last_range;
                const auto [c, d] = drs[i];
                
                const Lng splitted = (ops_count + 1) * (letters_count + d - c + 1);
                const Lng merged = ops_count * (d - a + 1);
                
                if (merged < splitted) {
                    letters_count -= (b - a + 1);
                    letters_count += (d - a + 1);
                    last_range = {a, d};
                } else {
                    letters_count += (d - c + 1);
                    ++ops_count;
                    last_range = drs[i];
                }
            }
            
            cout << ops_count * letters_count << endl;
        } else {
            cout << 0 << endl;
        }
    }
    
    return 0;
}
