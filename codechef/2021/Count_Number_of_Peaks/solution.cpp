#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

int extr_num(const vi &xs) {
    int ans{};

    for (int i = 1; i < sz(xs) - 1; ++i) {
        if ((xs[i - 1] < xs[i] && xs[i] > xs[i + 1]) ||
            (xs[i - 1] > xs[i] && xs[i] < xs[i + 1])) {
            ++ans;
        }
    }

    return ans;
}

int extr_num(const int n) {
    vvi src(n, vi{0, 1, 2});
    int ans{};

    for (const auto &xs : cartesian_product(src)) {
        ans += extr_num(xs);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        cout << extr_num(n) << '\n';
    }

    return 0;
}
