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

template <typename T>
constexpr bool intersect(const pair<T, T> &a, const pair<T, T> &b) {
    return !(a.second < b.first || a.first > b.second);
}

int count_intersecting_pairs(const vector<pair<double, double>> &ivs) {
    int ans = 0;

    for (int i = 0; i < sz(ivs) - 1; ++i) {
        for (int j = i + 1; j < sz(ivs); ++j) {
            if (intersect(ivs[i], ivs[j])) ++ans;
        }
    }

    return ans;
}

static constexpr double EPS = 0.0000001;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<pair<double, double>> ivs;
    ivs.reserve(n / 2);

    for (int i = 0; i < n; ++i) {
        int t;
        double a, b;
        cin >> t >> a >> b;

        if (t == 1) {
            ivs.emplace_back(a, b);
        } else if (t == 2) {
            if (a <= b - EPS) ivs.emplace_back(a, b - EPS);
        } else if (t == 3) {
            if (a + EPS <= b) ivs.emplace_back(a + EPS, b);
        } else if (t == 4) {
            if (a + EPS <= b - EPS) ivs.emplace_back(a + EPS, b - EPS);
        }
    }

    cout << count_intersecting_pairs(ivs) << '\n';
    return 0;
}
