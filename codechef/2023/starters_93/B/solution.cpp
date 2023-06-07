#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint n_choose_2(const mint n) { return n * (n - 1) / mint{2}; }

mint num_good_removals(const vector<int> &xs) {
    const auto total = accumulate(cbegin(xs), cend(xs), 0LL);
    const auto od =
        inof(count_if(cbegin(xs), cend(xs), [](const int x) { return x % 2; }));
    const auto ev = sz(xs) - od;

    if (total % 2LL) {
        assert(od);
        const auto od_ps = (od - 1) / 2;
        return od * mint{2}.pow(ev) * mint{2}.pow(od_ps);
    } else {
        mint ans{};

        if (ev) {
            ans += ev * mint{2}.pow(ev - 1) * mint{2}.pow(od / 2);
        }

        if (od) {
            const auto od_ps = od / 2;
            ans += n_choose_2(od_ps) * mint{2}.pow(od_ps - 1) * mint{2}.pow(ev);
        }

        return ans;
    }
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
