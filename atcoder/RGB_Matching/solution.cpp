#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int color_index(const char c) {
    if (c == 'R') return 0;
    return c == 'G' ? 1 : 2;
}

using iter = vll::const_iterator;
static constexpr ll INF = 1e17;

pair<iter, iter> closest_pair(const vll &xs, const vll &zs) {
    pair<iter, iter> ans{cend(xs), cend(zs)};
    ll best = INF;

    for (auto it = cbegin(xs); it != cend(xs); ++it) {
        const auto jt = lower_bound(cbegin(zs), cend(zs), *it);
        if (jt != cend(zs) && abs(*jt - *it) < best) {
            best = abs(*jt - *it);
            ans = pair{it, jt};
        }

        if (jt != cbegin(zs) && abs(*prev(jt) - *it) < best) {
            best = abs(*prev(jt) - *it);
            ans = pair{it, prev(jt)};
        }
    }

    assert((ans != pair{cend(xs), cend(zs)}));
    return ans;
}

ll min_delta(const vll &xs, const vll &zs) {
    const auto [it, jt] = closest_pair(xs, zs);
    return abs(*it - *jt);
}

ll min_delta(const vll &xs, const vll &ys, vll zs) {
    if (zs.empty()) return INF;

    const auto [it1, jt1] = closest_pair(xs, zs);
    const auto d1 = abs(*it1 - *jt1);

    zs.erase(jt1);
    if (zs.empty()) return INF;

    const auto [it2, jt2] = closest_pair(ys, zs);
    const auto d2 = abs(*it2 - *jt2);

    return d1 + d2;
}

ll min_total_dissatisfaction(const vector<pair<ll, char>> &acs) {
    array<vll, 3> xs{};
    for (const auto [a, c] : acs) xs[color_index(c)].push_back(a);

    if (all_of(cbegin(xs), cend(xs),
               [](const auto &row) { return sz(row) % 2 == 0; })) {
        return 0;
    }

    for (auto &row : xs) sort(begin(row), end(row));
    const auto e = [&xs]() -> int {
        if (sz(xs[0]) % 2 == 0) return 0;
        if (sz(xs[1]) % 2 == 0) return 1;
        return 2;
    }();

    const auto o1 = (e + 1) % 3;
    const auto o2 = (e + 2) % 3;

    assert(sz(xs[o1]) % 2 == 1);
    assert(sz(xs[o2]) % 2 == 1);

    return min({min_delta(xs[o1], xs[o2]), min_delta(xs[o1], xs[o2], xs[e]),
                min_delta(xs[o2], xs[o1], xs[e])});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<pair<ll, char>> acs(2 * n);
    for (auto &[a, c] : acs) cin >> a >> c;

    cout << min_total_dissatisfaction(acs) << '\n';
    return 0;
}
