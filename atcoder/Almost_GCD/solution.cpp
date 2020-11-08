#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    map<int, int> cbk;
    for (const auto x : xs) {
        ++cbk[x];

        const int lim = sqrt(x);
        for (int i = 2; i <= lim; ++i) {
            if (x % i == 0) {
                ++cbk[i];
                if (x / i > lim) {
                    ++cbk[x / i];
                }
            }
        }
    }

    int best_k = -1;
    int best_c = 0;
    for (const auto [k, v] : cbk) {
        if (v > best_c) {
            best_k = k;
            best_c = v;
        }
    }

    cout << best_k << '\n';

    return 0;
}
