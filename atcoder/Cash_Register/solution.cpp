#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

vector<pair<char, int>> run_length_encoding(const string &xs) {
    vector<pair<char, int>> result{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == result.back().first) {
            ++(result.back().second);
        } else {
            result.emplace_back(xs[i], 1);
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const auto ys = run_length_encoding(xs);
    int result{};

    for (const auto &[d, k] : ys) {
        if (d == '0') {
            result += div_ceil(k, 2);
        } else {
            result += k;
        }
    }

    cout << result << '\n';
    return 0;
}
