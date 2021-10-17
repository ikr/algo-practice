#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) { return static_cast<int>(x); }
template <typename T> constexpr ll llof(const T x) { return static_cast<ll>(x); }
template <typename T> constexpr double doof(const T x) { return static_cast<double>(x); }

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<string, string> rotation_edges(const string &s) {
    set<string> ss;

    for (int i = 0; i < sz(s); ++i) {
        string buf = s;
        rotate(begin(buf), next(begin(buf), i), end(buf));
        ss.insert(buf);
    }

    return {*cbegin(ss), *crbegin(ss)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    string s;
    cin >> s;

    const auto [lo, hi] = rotation_edges(s);
    cout << lo << '\n' << hi << '\n';
    return 0;
}
