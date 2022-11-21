#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1'000'000'007;

bool is_valley(const vector<int> &xs) {
    int c{};

    for (int i = 0; i < sz(xs); ++i) {
        const auto a = i ? xs[i - 1] : INF;
        const auto b = (i < sz(xs) - 1) ? xs[i + 1] : INF;
        c += (a > xs[i]) && (xs[i] < b);
    }

    return c == 1;
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
        xs.erase(unique(begin(xs), end(xs)), end(xs));

        cout << (is_valley(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
