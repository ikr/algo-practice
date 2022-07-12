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

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int min_ops_in_a_circle(const string &xs) {
    const auto ones = count(cbegin(xs), cend(xs), '1');
    const auto zeros = count(cbegin(xs), cend(xs), '0');
    if (!ones || !zeros) return 0;
    return inof(min(ones, zeros));
}

int min_ops(const vector<string> &grid) {
    const auto n = sz(grid);
    int result{};

    for (int i = 0; i < div_ceil(n, 2); ++i) {
        const auto d = n - 2 * i;
        set<pii> coord;

        for (int j = 0; j < d; ++j) {
            coord.emplace(i, i + j);
            coord.emplace(i + j, i);
            coord.emplace(i + d - 1, i + j);
            coord.emplace(i + j, i + d - 1);
        }

        cerr << "i:" << i << "coord:" << coord << endl;

        string xs;
        for (const auto &[ro, co] : coord) {
            xs += grid[ro][co];
        }
        result += min_ops_in_a_circle(xs);
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

        vector<string> grid(n);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == n);
        }

        cout << min_ops(grid) << '\n';
    }

    return 0;
}
