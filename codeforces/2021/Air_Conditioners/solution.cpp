#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

void combine_temperatures(const vi &xs, vi &ts) {
    const int k = sz(xs);

    {
        int lo = 0;
        for (int i = 1; i < k; ++i) {
            if (ts[i] >= ts[lo] + xs[i] - xs[lo]) {
                ts[i] = ts[lo] + xs[i] - xs[lo];
            }

            lo = i;
        }
    }

    {
        int lo = k - 1;
        for (int i = k - 2; i >= 0; --i) {
            if (ts[i] >= ts[lo] + xs[lo] - xs[i]) {
                ts[i] = ts[lo] + xs[lo] - xs[i];
            }

            lo = i;
        }
    }
}

vi temperatures(const int n, const vi &xs, vi ts) {
    combine_temperatures(xs, ts);
    const int k = sz(xs);
    vi ans(n, 0);

    for (int x = 0; x < n; ++x) {
        const auto jt = lower_bound(cbegin(xs), cend(xs), x);
        const auto it = (jt == cbegin(xs)) ? cbegin(xs) : prev(jt);

        const int i = min(k - 1, inof(distance(cbegin(xs), it)));
        const int j = min(k - 1, inof(distance(cbegin(xs), jt)));

        ans[x] = min(ts[i] + abs(x - xs[i]), ts[j] + abs(x - xs[j]));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> q;
    while (q--) {
        int n, k;
        cin >> n >> k;

        vector<pii> ps(k);
        for (auto &[x, _] : ps) {
            cin >> x;
            --x;
        }
        for (auto &[_, t] : ps) cin >> t;

        sort(begin(ps), end(ps));
        vi xs(k);
        vi ts(k);
        for (int i = 0; i < k; ++i) {
            xs[i] = ps[i].first;
            ts[i] = ps[i].second;
        }

        cout << temperatures(n, xs, move(ts)) << '\n';
    }

    return 0;
}
