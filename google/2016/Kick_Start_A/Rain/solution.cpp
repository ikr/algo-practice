#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;
using usi = unordered_set<int>;
using pi = pair<int, int>;
using vll = vector<ll>;
using vd = vector<double>;
using vs = vector<string>;
static const ll M = 1e9 + 7;
template <typename T> constexpr int intof(const T x) { return static_cast<int>(x); }

int solve (const vvi &rows) {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        int R, C;
        cin >> R >> C;
        vvi rows(R, vi(C, 0));
        
        for (auto &row : rows) {
            for (auto &x : row) cin >> x;
        }
        
        cout << "Case #" << i << ": " << solve(rows) << '\n';
    }

    return 0;
}
