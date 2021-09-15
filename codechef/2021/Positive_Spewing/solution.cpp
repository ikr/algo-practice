#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi positive_indices(const vi &xs) {
    vi ans;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i]) ans.push_back(i);
    }

    return ans;
}

pii dl_dr(const int n, const vi &idx, const int i) {
    assert(!idx.empty());
    const auto it = lower_bound(cbegin(idx), cend(idx), i);

    if (it == cend(idx)) {
        const int neigh_l = *prev(it);
        const int neigh_r = idx[0];
        return {i - neigh_l, (n - 1) - i + neigh_r + 1};
    }

    if (it == cbegin(idx)) {
        const int neight_l = idx.back();
        const int neight_r = *it;
        return {i + (n - 1) - neight_l + 1, neight_r - i};
    }

    {
        const int neigh_l = *prev(it);
        const int negih_r = *it;
        return {i - neigh_l, negih_r - i};
    }
}

int adj_num(const vi &xs, const int i) {
    const int n = sz(xs);
    int ans = 0;
    if (xs[(i - 1 + n) % n]) ++ans;
    if (xs[(i + 1) % n]) ++ans;
    return ans;
}

ll safe_sum(const vi &xs) {
    vll acc(sz(xs));
    copy(cbegin(xs), cend(xs), begin(acc));
    return accumulate(cbegin(acc), cend(acc), 0LL);
}

ll sum_after_k_sec(const vi &xs, const int k) {
    if (!k) return safe_sum(xs);

    const auto idx = positive_indices(xs);
    if (idx.empty()) return 0;

    vll acc(sz(xs), 0);

    for (int i = 0; i < sz(xs); ++i) {
        const auto a = adj_num(xs, i);

        if (a == 2) {
            acc[i] = xs[i] + k * 2LL;
            continue;
        }

        if (xs[i]) {
            acc[i] = xs[i];
            if (a == 1) ++acc[i];
            acc[i] += (k - 1LL) * 2LL;
            continue;
        }

        if (a == 1) {
            acc[i] = 1;

            if (k > 1) {
                ++acc[i];
                const auto n = sz(xs);
                const auto a2 = (xs[(i - 1 + n) % n] && xs[(i + 2) % n]) ||
                                (xs[(i - 2 + n) % n] && xs[(i + 1) % n]);

                if (a2) ++acc[i];
                acc[i] += (k - 2LL) * 2LL;
            }

            continue;
        }

        const auto [dl, dr] = dl_dr(sz(xs), idx, i);
        if (min(dl, dr) > k) continue;

        if (dl == dr) {
            acc[i] = (k - dl + 1LL) * 2LL;
            continue;
        }

        int k_ = k;
        k_ -= min(dl, dr) - 1;

        if (k_) {
            acc[i] = 1;
            --k_;
        }

        if (k_) {
            ++acc[i];
            --k_;
        }

        acc[i] += k_ * 2LL;
        if (abs(dl - dr) == 1 && k > 2) ++acc[i];
    }

    return accumulate(cbegin(acc), cend(acc), 0LL);
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

        cout << sum_after_k_sec(xs, k) << '\n';
    }

    return 0;
}
