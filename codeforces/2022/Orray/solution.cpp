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

constexpr int mlog2(const int x) {
    return 8U * sizeof(int) - __builtin_clz(x) - 1;
}

vector<int> optimal_order(vector<int> xs) {
    const auto it_max = max_element(cbegin(xs), cend(xs));
    const auto head = *it_max;
    xs.erase(it_max);

    array<vector<int>, 32> by_hi_bit;
    by_hi_bit.fill({});

    for (const auto x : xs) {
        by_hi_bit[mlog2(x)].push_back(x);
    }

    for (auto &row : by_hi_bit) {
        sort(begin(row), end(row), [](const auto a, const auto b) {
            return __builtin_popcount(a) > __builtin_popcount(b);
        });
    }

    return xs;
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

        cout << optimal_order(move(xs)) << '\n';
    }

    return 0;
}
