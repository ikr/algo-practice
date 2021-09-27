#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<ll, ll> num_boxes_and_total(const vi &amounts, const vi &limits) {
    const ll total =
        accumulate(cbegin(amounts), cend(amounts), 0LL,
                   [](const ll acc, const int x) { return acc + x; });

    ll ans = total;
    assert(sz(amounts) == sz(limits));

    for (int i = 0; i < sz(amounts); ++i) {
        if (!limits[i]) continue;
        ans = min(ans, llof(amounts[i] / limits[i]));
    }

    while (total % ans) --ans;
    assert(ans >= 0LL);
    return {ans, total};
}

vvi distribution(const vi &amounts, const vi &limits) {
    const auto [n, total] = num_boxes_and_total(amounts, limits);
    assert(total % n == 0LL);
    const auto m = total / n;

    vvi ans(n);
    for (auto &box : ans) box.reserve(m);
    vi rest(sz(amounts), 0);

    assert(sz(amounts) == sz(limits));
    for (int i = 0; i < sz(amounts); ++i) {
        if (limits[i]) {
            const auto chunks_num = amounts[i] / limits[i];

            const auto boxes_filled = inof(min(n, llof(chunks_num)));
            for (int j = 0; j < boxes_filled; ++j) {
                ans[j].insert(cend(ans[j]), limits[i], i + 1);
            }

            rest[i] = inof(amounts[i] - limits[i] * boxes_filled);
        } else {
            rest[i] = amounts[i];
        }
    }

    for (int i = 0, j = 0; i < sz(rest);) {
        if (!rest[i]) {
            ++i;
            continue;
        }

        if (sz(ans[j]) == m) {
            ++j;
            continue;
        }

        assert(llof(sz(ans[j])) < m);
        const auto batch = inof(min(llof(rest[i]), m - sz(ans[j])));
        ans[j].insert(cend(ans[j]), batch, i + 1);
        rest[i] -= batch;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k;
    cin >> k;

    vi amounts(k);
    for (auto &a : amounts) cin >> a;

    vi limits(k);
    for (auto &l : limits) cin >> l;

    const auto ans = distribution(amounts, limits);
    cout << sz(ans) << ' ' << sz(ans[0]) << '\n' << ans;

    return 0;
}
