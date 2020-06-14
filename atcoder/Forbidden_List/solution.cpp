#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using usi = unordered_set<int>;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int x, sz;
    cin >> x >> sz;
    vi ps(sz, 0);
    for (auto &p : ps) cin >> p;

    const usi ps_set(ps.cbegin(), ps.cend());

    for (int d = 0;; ++d) {
        if (!ps_set.count(x - d)) {
            cout << x - d << '\n';
            break;
        } else if (!ps_set.count(x + d)) {
            cout << x + d << '\n';
            break;
        }
    }

    return 0;
}
