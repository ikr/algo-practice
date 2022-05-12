#include <bits/stdc++.h>
using namespace std;

static constexpr array<int, 4> DS{1, 2, 5, 10};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
vector<vector<T>> cartesian_product(const vector<vector<T>> &src) {
    vector<vector<T>> result;
    if (src.empty() || any_of(cbegin(src), cend(src),
                              [](const auto &xs) { return xs.empty(); })) {
        return result;
    }

    result.push_back(vector<T>{});
    for (const auto &xs : src) {
        vector<vector<T>> next_gen;

        for (const auto x : xs) {
            for (auto curr : result) {
                curr.push_back(x);
                next_gen.push_back(curr);
            }
        }

        result = next_gen;
    }

    return result;
}

vector<int> zero_to_x(const int x) {
    vector<int> xs(x + 1);
    iota(begin(xs), end(xs), 0);
    return xs;
}

int num_cans(const array<int, 4> &wallet, const int k) {
    vector<vector<int>> src(4);
    for (int i = 0; i < 4; ++i) {
        src[i] = zero_to_x(wallet[i]);
    }

    int result{};

    for (const auto pr : cartesian_product(src)) {
        int cur{};

        int value{};
        for (int i = 0; i < 4; ++i) {
            value += pr[i] * DS[i];
        }

        if (value >= k) {
            ++cur;
            cur += num_cans(array<int, 4>{wallet[0] - pr[0], wallet[1] - pr[1],
                                          wallet[2] - pr[2], wallet[3] - pr[3]},
                            k);
        }

        result = max(result, cur);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        array<int, 4> wallet{};
        for (auto &a : wallet) cin >> a;
        cout << num_cans(wallet, k) << '\n';
    }

    return 0;
}
