#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string replace_all(string xs, const string &s, const string &t) {
    string::size_type i = 0;

    while ((i = xs.find(s, i)) != xs.npos) {
        xs.replace(i, sz(s), t);
        i += sz(t);
    }

    return xs;
}

string decode(const string &xs) {
    return replace_all(replace_all(xs, "zero", "0"), "one", "1");
}

char compare(const string &xs, const string &ys) {
    if (sz(xs) == sz(ys)) {
        if (xs == ys) return '=';
        return xs < ys ? '<' : '>';
    }

    return sz(xs) < sz(ys) ? '<' : '>';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs, ys;
    cin >> xs >> ys;

    cout << compare(decode(xs), decode(ys)) << '\n';
    return 0;
}
