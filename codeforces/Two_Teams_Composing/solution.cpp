#include <bits/stdc++.h>

using namespace std;

string pattern(const int sz) {
    string ans(sz, ' ');
    iota(ans.begin(), ans.end(), 'a');
    return ans;
}

string repeat(const string &s, const int times) {
    string ans;
    for (int i = 0; i < times; ++i) ans += s;
    return ans;
}

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i != t; ++i) {
        int n;
        cin >> n;
        
        unordered_set<int> distinct;
        map<int, int> counts_by_skill;
        
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            distinct.insert(x);
            ++counts_by_skill[x];
        }
        
        int ans = 0;
        const int ds = distinct.size(); 
        
        for (auto [s, c] : counts_by_skill) {
            ans = max({
                ans, 
                min(ds, c - 1),
                min(ds - 1, c)
            });
        }
        
        cout << ans << '\n';
    }
    
    cout << endl;

    return 0;
}
