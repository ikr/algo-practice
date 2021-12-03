#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi gather_ones_freqs(const vector<string> &xss) {
    vi ans(sz(xss[0]), 0);

    for (const auto &xs : xss) {
        for (int i = 0; i < sz(xs); ++i) {
            if (xs[i] == '1') ++ans[i];
        }
    }

    return ans;
}

ll as_ll(const string &bits) { return llof(bitset<30>(bits).to_ulong()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll power_consumption(const vector<string> &xss) {
    const int n = sz(xss);
    const auto fs = gather_ones_freqs(xss);

    string gamma_rate(sz(fs), ' ');
    string epsilon_rate(sz(fs), ' ');
    const int maj = div_ceil(n, 2);

    for (int i = 0; i < sz(fs); ++i) {
        if (fs[i] >= maj) {
            gamma_rate[i] = '1';
            epsilon_rate[i] = '0';
        } else {
            gamma_rate[i] = '0';
            epsilon_rate[i] = '1';
        }
    }

    return as_ll(gamma_rate) * as_ll(epsilon_rate);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<string> xss;

    for (string line; getline(cin, line);) {
        xss.push_back(line);
    }

    cout << power_consumption(xss) << '\n';
    return 0;
}
