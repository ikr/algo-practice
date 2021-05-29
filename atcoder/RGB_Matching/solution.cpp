#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

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
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int color_index(const char c) {
    if (c == 'R') return 0;
    return c == 'G' ? 1 : 2;
}

template <typename T>
T immediately_under(const vector<T> &xs, const T &x, const T &when_missing) {
    auto it = lower_bound(cbegin(xs), cend(xs), x);
    return it == xs.cbegin() ? when_missing : *(--it);
}

ll min_total_dissatisfaction(const vll &xs, const vll &ys) {
    ll ans = 1e17;

    for (const auto x : xs) {
        const auto o1 = lower_bound(cbegin(ys), cend(ys), x);
        const auto v1 = (o1 == cend(ys)) ? llof(1e19) : *o1;
        const auto v2 = immediately_under(ys, x, llof(1e18));

        ans = min(ans, min(abs(x - v1), abs(x - v2)));
    }

    return ans;
}

ll min_total_dissatisfaction(const vector<pair<ll, char>> &acs) {
    vvll xs(3);

    for (const auto [a, c] : acs) {
        xs[color_index(c)].push_back(a);
    }

    for (auto &row : xs) {
        sort(begin(row), end(row));
    }

    for (auto it = cbegin(xs); it != cend(xs);) {
        if (it->size() % 2 == 0) {
            it = xs.erase(it);
        } else {
            ++it;
        }
    }

    if (xs.empty()) return 0;
    assert(xs.size() == 2);

    return min_total_dissatisfaction(xs[0], xs[1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vector<pair<ll, char>> acs(2 * n);
    for (auto &[a, c] : acs) cin >> a >> c;

    cout << min_total_dissatisfaction(acs) << '\n';
    return 0;
}
