#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<int> digits_reversed(T n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vector<int> digits(T n) {
    auto ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

template <typename T> T number(const vector<int> &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

void remove_leading_zeros(vector<int> &ds) {
    for (auto it = ds.begin(); it != ds.end();) {
        if (*it != 0) break;
        it = ds.erase(it);
    }
}

int num_matches(const int n, const int b) {
    if (b == 1) return n;

    int result{};
    for (int a = 1; a <= n; ++a) {
        const auto ds = digits(a);
        if (all_of(cbegin(ds), cend(ds),
                   [b](const int d) { return d % b == 0; })) {
            ++result;
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        int b;
        cin >> n >> b;

        cout << num_matches(n, b) << '\n';
    }

    return 0;
}
