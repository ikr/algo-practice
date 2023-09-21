#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int min_ops(const string &xs, const int k) {
    const auto rle = run_length_encode(xs);
    int rest{};
    int result{};

    for (const auto &[x, f0] : rle) {
        if (x == 'W') {
            rest -= min(rest, f0);
            continue;
        }

        assert(x == 'B');
        auto f = f0;
        const auto adv = min(f, rest);
        f -= adv;
        rest -= adv;
        if (f == 0) continue;

        const auto ops = div_ceil(f, k);
        result += ops;

        if (f % k) {
            const auto tail = k - (f % k);
            rest = max(rest, tail);
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
        int n, k;
        cin >> n >> k;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << min_ops(xs, k) << '\n';
    }

    return 0;
}
