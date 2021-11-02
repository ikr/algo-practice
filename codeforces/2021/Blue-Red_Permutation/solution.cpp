#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) { return static_cast<int>(x); }
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_be_transformed(const vi &xs, const string &cs) {
    const int n = sz(xs);
    vector<pii> ps(n);

    for (int i = 0; i < n; ++i) {
        ps[i] = (cs[i] == 'B') ?
            pii{min(1, xs[i]), min(n, xs[i])} :
            pii{max(1, xs[i]), max(n, xs[i])};
    }

    sort(begin(ps), end(ps));

    for (int i = 0; i < n; ++i) {
        const int y = i + 1;
        const auto [a, b] = ps[i];
        if (!(a <= y && y <= b)) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        string cs;
        cin >> cs;

        const bool ans = can_be_transformed(xs, cs);
        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
