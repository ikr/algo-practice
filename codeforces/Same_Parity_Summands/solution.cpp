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

vi solve(const int n, const int k) {
    if (n < k) return {};
    
    if ((n % 2 == 0 && k % 2 == 0) || (n % 2 == 1 && k % 2 == 1)) {
        vi ans(k - 1, 1);
        ans.push_back(n - k + 1);
        return ans;
    } else if (n % 2 == 0 && k % 2 == 1) {
        if (2 * k > n) return {};
        vi ans(k - 1, 2);
        ans.push_back(n - 2 * (k - 1));
        return ans;
    }
    
    return {};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i != t; ++i) {
        int n, k;
        cin >> n >> k;
        
        vi ans = solve(n, k);
        
        if (ans.empty()) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (const int x : ans) cout << x << " ";
            cout << '\n';
        }
    }

    return 0;
}
