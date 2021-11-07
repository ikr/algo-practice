#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
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

template <typename T> constexpr T sign(const T x) {
    if (x == 0) return 0;
    return (x < 0) ? -1 : 1;
}

int min_spells(const vector<pii> &towns) {
    set<pii> spells;

    for (int i = 0; i < sz(towns); ++i) {
        for (int j = 0; j < sz(towns); ++j) {
            if (i == j) continue;

            const auto [xi, yi] = towns[i];
            const auto [xj, yj] = towns[j];

            const auto a = xi - xj;
            const auto b = yi - yj;

            const auto d = [&]() -> int {
                if (!a && !b) return 1;
                return (a && b) ? gcd(abs(a), abs(b)) : max(abs(a), abs(b));
            }();

            spells.emplace(sign(a) * abs(a) / d, sign(b) * abs(b) / d);
        }
    }

    return sz(spells);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vector<pii> towns(n);
    for (auto &[x, y] : towns) cin >> x >> y;

    cout << min_spells(towns) << '\n';
    return 0;
}
