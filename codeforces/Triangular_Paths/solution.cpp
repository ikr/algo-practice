#include <bits/stdc++.h>
using namespace std;

#define exp_eq(x, y)                                                           \
    ((x) == (y) ? 1                                                            \
                : ((cerr << (#x) << " != " << y << ", was " << x << '\n'), 0))

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int div_ceil(const int x, const int y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int path_min_cost(const pii coord) {
    const auto [ro, co] = coord;
    if (ro == co) return ro - 1;

    return (ro - co) / 2;
}

int path_min_cost(const vector<pii> &coords) {
    int ans = 0;

    for (auto it = cbegin(coords); it != cend(coords); ++it) {
        const pii last = it == cbegin(coords) ? pii{1, 1} : *prev(it);
        ans += path_min_cost(*it) - path_min_cost(last);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    exp_eq(path_min_cost(pii{2, 2}), 1);
    exp_eq(path_min_cost(pii{1, 1}), 0);
    exp_eq(path_min_cost(pii{6, 5}), 0);
    exp_eq(path_min_cost(pii{7, 2}), 2);
    exp_eq(path_min_cost(pii{8, 1}), 3);
    exp_eq(path_min_cost(pii{9, 1}), 4);
    exp_eq(path_min_cost(pii{5, 2}), 1);
    exp_eq(path_min_cost(pii{5, 1}), 2);
    exp_eq(path_min_cost(pii{6, 1}), 2);
    exp_eq(path_min_cost(pii{7, 1}), 3);
    exp_eq(path_min_cost(pii{8, 1}), 3);
    exp_eq(path_min_cost(pii{6, 3}), 1);
    exp_eq(path_min_cost(pii{6, 4}), 1);
    exp_eq(path_min_cost(pii{6, 2}), 2);
    exp_eq(path_min_cost(pii{8, 2}), 3);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> coords(n);
        for (auto &[ro, _] : coords) cin >> ro;
        for (auto &[_, co] : coords) cin >> co;

        sort(begin(coords), end(coords));
        cout << path_min_cost(coords) << '\n';
    }

    return 0;
}
