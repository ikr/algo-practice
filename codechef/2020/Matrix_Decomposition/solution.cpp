#include <bits/stdc++.h>

using namespace std;

using Lng = long long;
static const Lng M = 1e9 + 7;

Lng mexp(const Lng base, const Lng power) {
    if (power == 0) return 1;
    
    if (power % 2) {
        return (base * mexp(base, power - 1)) % M;
    }
    
    const Lng sq = mexp(base, power / 2);
    return (sq * sq) % M;
}

int main() {
    int t;
    cin >> t;
    
    for (int tc = 0; tc < t; ++tc) {
        int n, a;
        cin >> n >> a;
        
        vector<Lng> p(n + 1, a);
        p[0] = 0;
        
        Lng base = a;
        for (int i = 2; i <= n; ++i) {
            base = (base * p[i - 1]) % M;
            p[i] = mexp(base, 2 * i - 1);
        }
        
        const Lng ans = accumulate(p.cbegin(), p.cend(), 0, [](const Lng x, const Lng y) { return (x + y) % M; });
        cout << ans << endl;
    }
    
    return 0;
}
