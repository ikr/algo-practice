#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Op { A, B };

ostream &operator<<(ostream &os, const Op x) {
    if (x == Op::A) {
        os << 'A';
    } else {
        os << 'B';
    }
    return os;
}

pair<vector<int>, vector<int>> even_odd_split(const vector<int> &xs) {
    vector<int> ev;
    ev.reserve(sz(xs) / 2);
    vector<int> od;
    od.reserve(sz(xs) / 2);

    for (int i = 0; i < sz(xs); ++i) {
        if (i % 2 == 0) {
            ev.push_back(xs[i]);
        } else {
            od.push_back(xs[i]);
        }
    }

    return {ev, od};
}

vector<int> pebble_sort_indices(vector<int> &xs) {
    vector<int> result;

    for (int i = 0; i < sz(xs); ++i) {
        const auto jt = min_element(cbegin(xs) + i, cend(xs));
        const auto j = inof(distance(cbegin(xs), jt));

        for (int k = j - 1; k >= i; --k) {
            result.push_back(k);
            swap(xs[k], xs[k + 1]);
        }
    }

    return result;
}

vector<pair<Op, int>> sorting_program(const vector<int> &xs) {
    auto [ev, od] = even_odd_split(xs);

    vector<pair<Op, int>> result;

    for (const auto i : pebble_sort_indices(ev)) {
        result.emplace_back(Op::B, 2 * i + 1);
    }

    for (const auto i : pebble_sort_indices(od)) {
        result.emplace_back(Op::B, 2 * i + 1 + 1);
    }

    if (sz(od) != sz(ev)) {
        assert(sz(od) < sz(ev));
        od.push_back(INT_MAX);
    }

    for (int i = 0; i < sz(ev); ++i) {
        if (ev[i] > od[i]) {
            result.emplace_back(Op::A, 2 * i + 1);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    const auto ans = sorting_program(xs);
    cout << sz(ans) << '\n';

    for (const auto &[op, x] : ans) cout << op << ' ' << x << '\n';

    return 0;
}
