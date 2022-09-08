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

vector<pair<Op, int>> sorting_program(vector<int> xs) {
    vector<pair<Op, int>> result;

    for (int i = 0; i < sz(xs); ++i) {
        const auto jt = min_element(cbegin(xs) + i, cend(xs));
        auto j = inof(distance(cbegin(xs), jt));

        if ((j % 2) != (i % 2)) {
            result.emplace_back(Op::A, j - 1);
            swap(xs[j - 1], xs[j]);
            --j;
        }

        for (int k = j - 2; k >= i; k -= 2) {
            result.emplace_back(Op::B, k);
            swap(xs[k], xs[k + 2]);
        }
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
    for (auto &x : xs) cin >> x;

    const auto ans = sorting_program(move(xs));
    cout << sz(ans) << '\n';

    for (const auto &[op, x] : ans) cout << op << ' ' << x << '\n';

    return 0;
}
