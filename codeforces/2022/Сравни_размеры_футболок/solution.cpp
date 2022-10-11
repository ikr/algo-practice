#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

char ab_relation(const string &a, const string &b) {
    if (a == b) return '=';

    if (a == "M") {
        return b.back() == 'S' ? '>' : '<';
    }

    if (a.back() == 'S') {
        if (b == "M") return '<';
        if (b.back() == 'S') {
            assert(sz(a) != sz(b));
            return sz(a) > sz(b) ? '<' : '>';
        }

        assert(b.back() == 'L');
        return '<';
    }

    assert(a.back() == 'L');
    if (b == "M") return '>';
    if (b.back() == 'S') return '>';
    assert(b.back() == 'L');

    assert(sz(a) != sz(b));
    return sz(a) > sz(b) ? '>' : '<';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;
        cout << ab_relation(a, b) << '\n';
    }

    return 0;
}
