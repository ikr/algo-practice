#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> struct mmax final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

int max_happy(const vector<int> &xs) {
    const auto N = sz(xs);
    const auto mod_norm = [N](const int x) -> int { return ((x % N) + N) % N; };

    const auto xsxs = [&]() -> vector<int> {
        auto result = xs;
        result.insert(cend(result), cbegin(xs), cend(xs));
        return result;
    }();

    // D[i][j] is the length of an iota starting at i
    // from the number (xsxs[i] - 1 + j)
    vector<array<int, 3>> D(2 * N, array{1, 1, 1});

    for (int i = 2 * N - 2; i >= 0; --i) {
        for (int a = 0; a < 3; ++a) {
            for (int b = 0; b < 3; ++b) {
                if (mod_norm(xsxs[i] - 1 + a + 1) ==
                    mod_norm(xsxs[i + 1] - 1 + b)) {
                    D[i][a] = D[i + 1][b] + 1;
                }
            }
        }
    }

    const auto hi = transform_reduce(
        cbegin(D), cend(D), 1, mmax<int>{}, [](const auto &tri) -> int {
            return *max_element(cbegin(tri), cend(tri));
        });

    return min(hi, N);
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
