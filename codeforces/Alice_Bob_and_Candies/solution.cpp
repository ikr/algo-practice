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

struct Game {
    int moves;
    int a;
    int b;
};

Game solve(const vi &xs) {
    const int sz = xs.size();
    if (sz == 1) return {1, xs.front(), 0};
    
    int m = 0, a = 0, b = 0;
    int lo = 0, hi = sz - 1;
    int a_last = 0, b_last = 0;
    bool alice = true;
    
    while (lo <= hi) {
        if (alice) {
            int yield = 0;
            
            while (yield <= b_last && lo <= hi) {
                yield += xs[lo];
                ++lo;
            }
            
            a_last = yield;
            a += yield;
        } else {
            int yield = 0;
            
            while (yield <= a_last && lo <= hi) {
                yield += xs[hi];
                --hi;
            }
            
            b_last = yield;
            b += yield;
        }
        
        ++m;
        alice = !alice;
    }
    
    return {m, a, b};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i != t; ++i) {
        int sz;
        cin >> sz;
        
        vi xs(sz, 0);
        for (int &x : xs) cin >> x;
        
        const auto [m, a, b] = solve(xs);
        cout << m << ' ' << a << ' ' << b << '\n';
    }

    return 0;
}
