#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

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

static constexpr int X_MAX = 200'000;

map<int, vi> gather_indices(const vi &xs) {
    map<int, vi> ans;
    for (int i = 0; i < sz(xs); ++i) {
        ans[xs[i]].push_back(i);
    }
    return ans;
}

vi coloring(const vi &xs, const int k) {
    auto idx = gather_indices(xs);

    vi ans(sz(xs), 0);
    vi buf;
    buf.reserve(k);

    const auto flush_buf = [&]() {
        assert(sz(buf) == k);
        for (int j = 0; j < k; ++j) {
            ans[buf[j]] = j + 1;
        }
        buf.clear();
    };

    for (auto it = begin(idx); it != end(idx);) {
        auto &ii = it->second;

        if (sz(ii) >= k) {
            for (int j = 0; j < k; ++j) {
                ans[ii[j]] = j + 1;
            }

            ++it;
            continue;
        }

        const auto missing = k - sz(buf);
        assert(missing > 0);

        const auto moving = min(missing, sz(ii));
        assert(moving > 0);

        copy(cbegin(ii), next(cbegin(ii), moving), back_inserter(buf));
        ii.erase(cbegin(ii), next(cbegin(ii), moving));

        if (sz(buf) == k) {
            flush_buf();
        }

        if (ii.empty()) {
            ++it;
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

        vi xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << coloring(xs, k) << '\n';
    }

    return 0;
}
