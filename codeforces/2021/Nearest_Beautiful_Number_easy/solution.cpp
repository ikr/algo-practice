#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
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

vi gather_solos() {
    vi ans;
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            ans.push_back(number<int>(vi(i, j)));
        }
    }

    return ans;
}

int two_digits_combo(const int len, const int d1, const int d2,
                     const int bits) {
    assert(d1 != d2);
    vi ans(len, 0);

    for (int i = 0; i < sz(ans); ++i) {
        ans[i] = ((1 << i) & bits) ? d2 : d1;
    }

    return number<int>(ans);
}

vi gather_duos() {
    vi ans{1'000'000'000};

    for (int len = 2; len <= 9; ++len) {
        for (int bits = 1; bits < (1 << len) - 1; ++bits) {
            for (int i = 0; i <= 8; ++i) {
                for (int j = i + 1; j <= 9; ++j) {
                    ans.push_back(two_digits_combo(len, i, j, bits));
                }
            }
        }
    }

    return ans;
}

pair<vi, vi> bound_tables() {
    auto a = gather_solos();
    auto b = gather_duos();
    copy(cbegin(a), cend(a), back_inserter(b));

    sort(begin(a), end(a));
    sort(begin(b), end(b));

    return {a, b};
}

int min_k_beautiful_bound(const vi &a, const vi &b, const int n, const int k) {
    const auto &xs = k == 1 ? a : b;
    return *lower_bound(cbegin(xs), cend(xs), n);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto [a, b] = bound_tables();
    assert(find(cbegin(b), cend(b), 221) != cend(b));

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << min_k_beautiful_bound(a, b, n, k) << '\n';
    }

    return 0;
}
