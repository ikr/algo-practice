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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_positive(const int x) { return x > 0; }

bool is_split(const bitset<10> &pins) {
    if (pins.test(1 - 1)) {
        return false;
    }

    array<int, 7> cs{0, 0, 0, 0, 0, 0, 0};
    cs[0] += pins.test(7 - 1);

    cs[1] += pins.test(4 - 1);

    cs[2] += pins.test(8 - 1);
    cs[2] += pins.test(2 - 1);

    cs[3] += pins.test(5 - 1);
    cs[3] += pins.test(1 - 1);

    cs[4] += pins.test(9 - 1);
    cs[4] += pins.test(3 - 1);

    cs[5] += pins.test(6 - 1);

    cs[6] += pins.test(10 - 1);

    // cerr << "cs:" << cs << '\n';

    for (int i = 1; i < sz(cs) - 1; ++i) {
        if (cs[i] > 0) continue;

        if (any_of(cbegin(cs), cbegin(cs) + i, is_positive) &&
            any_of(cbegin(cs) + i + 1, cend(cs), is_positive)) {
            return true;
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;
    reverse(begin(s), end(s));

    bitset<10> pins(s);
    cout << (is_split(pins) ? "Yes" : "No") << '\n';
    return 0;
}
