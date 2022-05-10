#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int ch_diff(const char x, const char y) { return abs(inof(x) - inof(y)); }

int s_diff(const string &x, const string &y) {
    int result{};
    for (int i = 0; i < sz(x); ++i) {
        result += ch_diff(x[i], y[i]);
    }
    return result;
}

int solve(const vector<string> &xs) {
    int result = 1e9;

    for (int i = 0; i < sz(xs) - 1; ++i) {
        for (int j = i + 1; j < sz(xs); ++j) {
            result = min(result, s_diff(xs[i], xs[j]));
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> xs(n);
        for (auto &x : xs) {
            cin >> x;
            assert(sz(x) == m);
        }

        cout << solve(xs) << '\n';
    }

    return 0;
}
