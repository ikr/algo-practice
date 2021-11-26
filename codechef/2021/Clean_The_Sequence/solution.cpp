#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi collapse_equal(const vi &xs) {
    vi ans{xs[0]};

    for (int i = 1; i < sz(xs); ++i) {
        if (ans.back() != xs[i]) {
            ans.push_back(xs[i]);
        }
    }

    return ans;
}

int initial_ugliness(const vi &xs) {
    int ans{};

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] != xs[i - 1]) ++ans;
    }

    return ans;
}

vi ugliness(const vi &xs, const int k) {
    const auto baseline = initial_ugliness(xs);
    if (sz(xs) == 1) return vi(k + 1, 0);

    vi ans(k + 1, baseline);
    for (int i = 0; i < sz(xs); ++i) {
        if (i == 0 || i == sz(xs) - 1) {
            --ans[xs[i]];
        } else {
            if (xs[i - 1] == xs[i + 1]) {
                ans[xs[i]] -= 2;
            } else {
                --ans[xs[i]];
            }
        }
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

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = ugliness(collapse_equal(xs), k);
        for (int i = 1; i < sz(ans); ++i) {
            if (i > 1) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
