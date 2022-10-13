#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Query = tuple<int, int, string>;

static constexpr int AZ = 26;

constexpr int az_to_i(const char c) {
    return static_cast<int>(c) - static_cast<int>('a');
}

bool less_than(const array<ll, AZ> &xs, const array<ll, AZ> &ys) {
    for (int i = 0; i < AZ; ++i) {
        if (xs[i] == ys[i]) continue;
        if (xs[i] < ys[i]) return true;
        return false;
    }

    return false;
}

vector<bool> answer_queries(const vector<Query> &qs) {
    array<ll, AZ> s;
    s.fill(0);
    s[0] = 1;

    array<ll, AZ> t;
    t.fill(0);
    t[0] = 1;

    vector<bool> result;
    result.reserve(sz(qs));

    for (const auto &[cmd, k, xs] : qs) {
        array<ll, AZ> &dest = cmd == 1 ? s : t;

        for (const auto x : xs) {
            dest[az_to_i(x)] += k;
        }

        result.push_back(less_than(s, t));
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<Query> qs(n);
        for (auto &[cmd, k, xs] : qs) cin >> cmd >> k >> xs;

        for (const auto ans : answer_queries(qs)) {
            cout << (ans ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
