#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> grid_for(const int N, const int bits) {
    assert(N <= 2);
    vector<string> grid(2 * N, string(2 * N, 'O'));

    for (int ro = 0; ro < 2 * N; ++ro) {
        for (int co = 0; co < 2 * N; ++co) {
            const auto d = ro * 2 * N + co;
            if ((1 << d) & bits) grid[ro][co] = 'I';
        }
    }

    return grid;
}

int str_diff_num(const string &xs, const string &ys) {
    assert(sz(xs) == sz(ys));
    int result{};
    for (int i = 0; i < sz(xs); ++i) {
        result += (xs[i] != ys[i]);
    }
    return result;
}

int diff_num(const vector<string> &xss, const vector<string> &yss) {
    assert(sz(xss) == sz(yss));
    return inner_product(cbegin(xss), cend(xss), cbegin(yss), 0, plus<int>{},
                         str_diff_num);
}

int ones_num(const string &xs, __attribute__((unused)) const string &_) {
    return inof(count(cbegin(xs), cend(xs), 'I'));
}

bool is_proper_horz(const vector<string> &grid) {
    const int N = sz(grid) / 2;
    const auto t = inner_product(cbegin(grid), cbegin(grid) + N, cbegin(grid),
                                 0, plus<int>{}, ones_num);
    const auto b = inner_product(cbegin(grid) + N, cend(grid), cbegin(grid), 0,
                                 plus<int>{}, ones_num);
    return t == b;
}

vector<string> transpose(const vector<string> &grid) {
    vector<string> result = grid;

    for (int ro = 0; ro < sz(grid); ++ro) {
        assert(sz(result) == sz(result[ro]));

        for (int co = 0; co < sz(grid); ++co) {
            result[ro][co] = grid[co][ro];
        }
    }

    return result;
}

bool is_proper_vert(const vector<string> &grid) {
    return is_proper_horz(transpose(grid));
}

bool is_proper(const vector<string> &grid) {
    return is_proper_horz(grid) && is_proper_vert(grid);
}

int min_ops_brute_force(const vector<string> &grid) {
    assert(sz(grid) % 2 == 0);
    const int N = sz(grid) / 2;
    assert(N <= 2);

    const auto S = sz(grid) * sz(grid);
    const auto LIM = (1 << S) - 1;
    int result = S;

    bool met_self = false;
    for (int bits = 0; bits <= LIM; ++bits) {
        const auto curr = grid_for(N, bits);
        if (curr == grid) met_self = true;

        if (is_proper(curr)) {
            result = min(result, diff_num(grid, curr));
        }
    }
    assert(met_self);

    return result;
}

int min_ops(const vector<string> &grid) {
    const int N = sz(grid) / 2;

    const auto sum_up = [&](const pair<int, int> iiro,
                            const pair<int, int> iico) -> int {
        int result{};
        for (int ro = iiro.first; ro < iiro.second; ++ro) {
            for (int co = iico.first; co < iico.second; co++) {
                result += grid[ro][co] == 'I';
            }
        }
        return result;
    };

    const auto A = sum_up({0, N}, {0, N});
    const auto B = sum_up({0, N}, {N, 2 * N});
    const auto C = sum_up({N, 2 * N}, {0, N});
    const auto D = sum_up({N, 2 * N}, {N, 2 * N});
    return abs(A - D) + abs(B - C);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<string> grid(2 * N);
        for (auto &row : grid) cin >> row;

        const auto result = min_ops(grid);
        // const auto bf_result = min_ops_brute_force(grid);
        // if (result != bf_result) {
        //     cerr << "ANS:" << result << " BF:" << bf_result << endl;
        // }
        // assert(result == bf_result);

        cout << "Case #" << i << ": " << result << '\n';
    }

    return 0;
}
