#include <bits/stdc++.h>
using namespace std;

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

optional<int> first_diff_index(const string &s, const string &t) {
    for (int i = 0; i < sz(s); ++i) {
        if (s[i] != t[i]) return i;
    }

    return nullopt;
}

string swapped(string xs, const int i, const int j) {
    swap(xs[i], xs[j]);
    return xs;
}

bool can_transform(const string &s, const string &t) {
    const auto ci = first_diff_index(s, t);
    if (!ci) return true;
    const auto i = *ci;

    if (i > 0) {
        if (swapped(s, i - 1, i) == t) return true;
        if (swapped(t, i - 1, i) == s) return true;
    }

    if (i < sz(s) - 1) {
        if (swapped(s, i, i + 1) == t) return true;
        if (swapped(t, i, i + 1) == s) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    string s, t;
    cin >> s >> t;

    const auto ans = can_transform(s, t);
    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
