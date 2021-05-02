#include <algorithm>
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;

    vector<array<int, 5>> xs(t);

    for (auto &[a, b, c, d, e] : xs) cin >> a >> b >> c >> d >> e;

    array<int, 5> agg{0, 0, 0, 0, 0};

    for (const auto x : xs) {
        for (int i = 0; i < 5; ++i) {
            agg[i] = max(agg[i], x[i]);
        }
    }

    cout << *min_element(cbegin(agg), cend(agg)) << '\n';

    return 0;
}
