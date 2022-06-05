#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

static constexpr int INF = 1'000'000'001;

bool is_possible(const int K, const vector<int> &xs) {
    if (K == 1) return true;
    const auto N = sz(xs);
    const auto W = div_ceil(N, K);

    vector<vector<int>> grid(K, vector(W, INF));

    for (int co = 0; co < W; ++co) {
        for (int ro = 0; ro < K; ++ro) {
            const auto i = co * K + ro;
            if (i < N) grid[ro][co] = xs[i];
        }
    }

    for (auto &row : grid) sort(begin(row), end(row));
    vector<int> ys(N);

    for (int co = 0; co < W; ++co) {
        for (int ro = 0; ro < K; ++ro) {
            const auto i = co * K + ro;
            if (i < N) ys[i] = grid[ro][co];
        }
    }

    return is_sorted(cbegin(ys), cend(ys));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << (is_possible(K, xs) ? "Yes" : "No") << '\n';
    return 0;
}
