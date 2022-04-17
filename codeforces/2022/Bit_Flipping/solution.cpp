#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

pair<string, vector<int>> solve(int k, const string &xs) {
    const bool odd = k % 2;
    string ys = xs;
    vector<int> ops(sz(xs), 0);

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') {
            if (odd) {
                if (k) {
                    ops[i] = 1;
                    --k;
                } else {
                    ys[i] = '0';
                }
            } else {
                continue;
            }
        } else {
            assert(xs[i] == '0');
            if (odd) {
                ys[i] = '1';
                continue;
            } else {
                if (k) {
                    ys[i] = '1';
                    ops[i] = 1;
                    --k;
                }
            }
        }
    }

    if (k) {
        ops[0] += (k % 2) ? (k - 1) : k;

        if (k % 2) {
            ++ops.back();
            ys.back() = (ys.back() == '1' ? '0' : '1');
        }
    }

    return {ys, ops};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs(n, ' ');
        cin >> xs;
        assert(sz(xs) == n);

        const auto [a, b] = solve(k, xs);
        cout << a << '\n' << b << '\n';
    }

    return 0;
}
