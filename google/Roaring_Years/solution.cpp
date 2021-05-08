#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi digits_reversed(ll n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % 10LL));
        n /= 10;
    }

    return ans;
}

vi digits(ll n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

ll number(const vi &ds) {
    if (ds.empty()) return 0;

    long long ans = 0;
    long long mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= 10LL;
    }
    return ans;
}

vi subvector(const vi &xs, const int i, const int l) {
    vi ans(cbegin(xs) + i, cbegin(xs) + i + l);
    return ans;
}

bool is_roaring(const int step, const vi &ds) {
    if (sz(ds) < 2 * step || sz(ds) % step != 0) return false;

    auto pre = number(subvector(ds, 0, step));
    for (int i = step; i + step <= sz(ds); i += step) {
        auto curr = number(subvector(ds, i, step));
        if (curr != pre + 1) return false;
        pre = curr;
    }

    return true;
}

bool is_roaring(const int x) {
    const auto ds = digits(x);
    for (int step = 1; step <= max(1, sz(ds) / 2); ++step) {
        if (is_roaring(step, ds)) return true;
    }
    return false;
}

int solve(int x) {
    assert(!is_roaring(100000));

    do {
        ++x;
    } while (!is_roaring(x));

    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int x;
        cin >> x;

        cout << "Case #" << i << ": " << solve(x) << '\n';
    }

    return 0;
}
