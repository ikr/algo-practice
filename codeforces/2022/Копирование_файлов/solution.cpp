#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using ll = long long;
using pll = pair<ll, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> prefix_sums(const vector<ll> &xs) {
    vector<ll> result(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(result));
    return result;
}

auto percent_intervals_none() {
    array<optional<pll>, 100> result;
    result.fill(nullopt);
    return result;
}

optional<pll> intersection(const pll &ab, const pll &cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    if (b < c || d < a) return nullopt;

    array<ll, 4> xs{a, b, c, d};
    sort(begin(xs), end(xs));
    return pll{xs[1], xs[2]};
}

vector<int> collision_points(const vector<ll> &xs) {
    const auto ss = prefix_sums(xs);
    const auto S = ss.back();

    const auto totals = [&]() {
        vector<array<optional<pll>, 100>> result(sz(xs),
                                                 percent_intervals_none());

        for (int i = 0; i < sz(xs); ++i) {
            ll pre{};

            for (int k = 1; k <= 99; ++k) {
                const auto lk_ =
                    ((k - 1) * S - 100 * (i ? ss[i - 1] : 0LL)) / 100;
                const auto lk = (k * S - 100 * (i ? ss[i - 1] : 0LL)) / 100;
                if (lk == lk_) continue;

                result[i][k] = pll{pre, lk_};
                pre = lk;
            }
        }

        return result;
    }();

    set<int> result{0, 100};

    for (int i = 0; i < sz(xs); ++i) {
        ll pre{};

        for (int k = 1; k <= 99; ++k) {
            const auto lk_ = (xs[i] * (k - 1)) / 100;
            const auto lk = (xs[i] * k) / 100;
            if (lk == lk_) continue;

            const pll ab{pre, lk_};

            for (int j = 0; j < sz(xs); ++j) {
                if (!totals[j][k]) continue;
                if (intersection(ab, *totals[j][k])) {
                    result.insert(k);
                    break;
                }
            }
        }
    }

    return vector(cbegin(result), cend(result));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<ll> xs(n);
    for (auto &x : xs) cin >> x;

    for (const auto x : collision_points(xs)) cout << x << '\n';
    return 0;
}
