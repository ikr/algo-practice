#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<int> &xs) {
    int ods{};
    vector<ll> evs;

    for (const auto x : xs) {
        if (x % 2) {
            ++ods;
        } else {
            evs.push_back(x);
        }
    }

    if (evs.empty()) return 0;
    if (ods) return sz(evs);

    if (any_of(cbegin(evs), cend(evs),
               [](const auto x) { return __builtin_ctzll(x) == 1; })) {
        return sz(evs);
    }

    const auto s = accumulate(cbegin(evs), cend(evs), 0LL);
    return sz(evs) - 1 + __builtin_ctzll(s);
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

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
