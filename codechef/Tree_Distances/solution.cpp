#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<int, vector<pii>> solution(const int x, const int y) {
    if (x < y || y % 2) return {0, {}};

    vector<pii> es;
    es.reserve(y / 2);

    for (int i = 1; i < y; i += 2) {
        es.emplace_back(i, i + 1);
    }

    return {x, es};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;

        const auto [n, es] = solution(x, y);
        if (n) {
            cout << "YES" << '\n' << n << '\n';

            for (const auto [u, v] : es) {
                cout << u << ' ' << v << '\n';
            }
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
