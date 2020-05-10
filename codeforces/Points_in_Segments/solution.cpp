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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    si ps;
    for (int i = 1; i <= m; ++i) ps.insert(i);
    
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        ps.erase(ps.lower_bound(a), ps.upper_bound(b));
    }
    
    cout << ps.size() << '\n';
    for (const int p : ps) {
        cout << p << " ";
    }
    cout << '\n';
    
    return 0;
}
