#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vi = vector<int>;
using vull = vector<ull>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

template <typename T> T number(const vi &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

vull precompute_all() {
    set<ull> ans;

    for (int d = -9; d <= 9; ++d) {
        for (int x0 = 1; x0 <= 9; ++x0) {
            vi curr{x0};

            while (0 <= curr.back() + d && curr.back() + d <= 9 &&
                   sz(curr) <= 18) {
                curr.push_back(curr.back() + d);
            }

            if (sz(curr) > 2) {
                ans.insert(number<ull>(curr));
            }
        }
    }

    return vull(cbegin(ans), cend(ans));
}

ull smallest_arithmetic_not_less_than(const ull x) {
    const auto ds = digits(x);
    if (sz(ds) < 3) return x;

    const auto xs = precompute_all();
    return *lower_bound(cbegin(xs), cend(xs), x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ull x;
    cin >> x;
    cout << smallest_arithmetic_not_less_than(x) << '\n';
    return 0;
}
