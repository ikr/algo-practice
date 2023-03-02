#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

int max_gain(const string &xs, const int k0) {
    vector<int> lo(AZ, 0);
    vector<int> up(AZ, 0);

    for (const auto x : xs) {
        if (islower(x)) {
            ++lo[inof(x) - 'a'];
        } else {
            assert(isupper(x));
            ++up[inof(x) - 'A'];
        }
    }

    int ans{};
    for (int i = 0, k = k0; i < AZ; ++i) {
        const auto initial_pairs = min(lo[i], up[i]);
        ans += initial_pairs;
        if (!k) continue;

        const auto r = max(lo[i] - initial_pairs, up[i] - initial_pairs);
        if (!(r / 2)) continue;

        const auto a = min(r / 2, k);
        k -= a;
        ans += a;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << max_gain(xs, k) << '\n';
    }

    return 0;
}
