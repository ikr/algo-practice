#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using si = set<int>;
using usi = unordered_set<int>;
using vll = vector<ll>;
static const ll M = 1e9 + 7;

vi digits(int n) {
    vi ans;
    
    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
}

int ipow(const int base, const int exp) {
    int ans = 1;
    for (int i = 1; i <= exp; ++i) ans *= base;
    return ans;
}

vi solve(const int n) {
    const auto ds = digits(n);
    const int sz = ds.size();
    vi ans;
    
    for (int i = sz - 1; i >= 0; --i) {
        if (ds[i] == 0) continue;
        ans.push_back(ds[i] * ipow(10, sz - 1 - i));
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i != t; ++i) {
        int n;
        cin >> n;
        
        vi ans = solve(n);
        cout << ans.size() << '\n';
        for (const int x : ans) cout << x << " ";
        cout << '\n';
    }

    return 0;
}
