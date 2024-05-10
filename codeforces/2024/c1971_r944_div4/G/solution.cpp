#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int hi_bits(const int x) { return x & (~3); }

vector<int> best_array(vector<int> xs) {
    map<int, vector<int>> src;
    for (int i = 0; i < sz(xs); ++i) {
        src[hi_bits(xs[i])].push_back(i);
    }

    auto dst = src;
    for (auto &[_, ii] : dst) {
        sort(begin(ii), end(ii),
             [&](const int i, const int j) { return xs[i] < xs[j]; });
    }

    auto ys = xs;
    for (const auto &[k, dii] : dst) {
        for (int j = 0; j < sz(dii); ++j) {
            ys[src[k][j]] = xs[dii[j]];
        }
    }

    return ys;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << best_array(std::move(xs)) << '\n';
    }

    return 0;
}
