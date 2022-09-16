#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_happy(const vector<int> &xs) {
    const auto N = sz(xs);
    const auto xsxs = [&]() -> vector<int> {
        auto result = xs;
        result.insert(cend(result), cbegin(xs), cend(xs));
        return result;
    }();

    // D[i][j] is the length of an iota starting at i
    // from the number (xsxs[i] - 1 + j)
    vector<array<int, 3>> D(2 * N, array{0, 0, 0});

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << max_happy(xs) << '\n';
    return 0;
}
