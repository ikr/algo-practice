#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr ll K = 27;

template <typename T> constexpr int llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

ll ipow(const ll base, const int exp) {
    ll result = 1LL;
    for (int i = 1; i <= exp; ++i) {
        result *= base;
    }
    return result;
}

ll hash_of(const string &xs) {
    ll result = 0LL;
    for (const auto x : xs) {
        result *= K;
        result += llof(x - '`');
    }
    return result;
}

vector<int> build_index(const string &haystack, const string &needle) {
    const int m = sz(needle);
    if (sz(haystack) < m) return vector<int>{};
    const auto target = hash_of(needle);
    const int n = sz(haystack);
    const ll q = ipow(K, m - 1);

    vector<int> result{};
    ll cur = hash_of(haystack.substr(0, m));
    if (cur == target) {
        result.push_back(0);
    }

    for (int shift = 1; shift + m <= n; ++shift) {
        const auto sub = llof(haystack[shift - 1] - '`') * q;
        cur -= sub;
        cur *= K;
        cur += llof(haystack[shift + m - 1] - '`');

        if (cur == target) {
            result.push_back(shift);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> q;

    string s, t;
    cin >> s >> t;

    vector<pii> range_queries;
    range_queries.reserve(q);

    while (q--) {
        int l, r;
        cin >> l >> r;
        range_queries.emplace_back(l - 1, r);
    }

    cerr << build_index(s, t) << '\n';
    return 0;
}
