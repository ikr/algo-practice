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

constexpr pair<Op, int> zero_based_to_one_based(const pair<Op, int> &command) {
    const auto [op, x] = command;
    return {op, x + 1};
}

int find_index(const vector<int> &xs, const int i0,
               const function<bool(int, int)> i_x_pred) {
    assert(i0 >= 0);
    assert(i0 < sz(xs));

    for (int i = i0; i < sz(xs); ++i) {
        if (i_x_pred(i, xs[i])) return i;
    }

    return -1;
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

vector<int> pebble_sort_indices(vector<int> xs) {
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

vector<pair<Op, int>> sorting_program(vector<int> xs) {
    vector<pair<Op, int>> result;

    for (int k = 0; k < sz(xs);) {
        const auto a = find_index(xs, k, [](const int i, const int x) -> bool {
            return (i % 2) != (x % 2);
        });

        if (a == -1) break;

        const auto b =
            find_index(xs, a + 1, [&](const int i, const int x) -> bool {
                return (i % 2) != (x % 2) && (x % 2) != (xs[a] % 2);
            });
        assert(b != -1);
        const auto bx = xs[b];

        for (int q = b - 2; q >= a + 1; q -= 2) {
            result.emplace_back(Op::B, q);
            swap(xs[q], xs[q + 2]);
        }
        assert(xs[a + 1] == bx);

        result.emplace_back(Op::A, a);
        swap(xs[a], xs[a + 1]);
        k = a + 2;
    }

    auto [ev, od] = even_odd_split(xs);

    for (const auto i : pebble_sort_indices(move(ev))) {
        result.emplace_back(Op::B, 2 * i);
    }

    for (const auto i : pebble_sort_indices(move(od))) {
        result.emplace_back(Op::B, 2 * i + 1);
    }

    transform(cbegin(result), cend(result), begin(result),
              zero_based_to_one_based);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    const auto ans = sorting_program(move(xs));
    cout << sz(ans) << '\n';

    for (const auto &[op, x] : ans) {
        cout << op << ' ' << x << '\n';
    }

    return 0;
}
