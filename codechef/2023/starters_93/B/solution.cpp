#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint n_choose_2(const mint n) { return n * (n - 1) * mint{2}.inv(); }

mint num_good_removals(const vector<int> &xs) {

    const auto od =
        inof(count_if(cbegin(xs), cend(xs), [](const int x) { return x % 2; }));
    const auto ev = sz(xs) - od;

    if (!ev) return 1;

    return mint{2}.pow(ev) - (od ? 0 : 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << num_good_removals(xs).val() << '\n';
    }

    return 0;
}
