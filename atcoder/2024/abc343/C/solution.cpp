#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lll = __int128_t;
using ulll = __uint128_t;

ostream &operator<<(ostream &dest, const lll value) {
    ostream::sentry s(dest);
    if (s) {
        ulll tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);

        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);

        if (value < 0) {
            --d;
            *d = '-';
        }

        const int len = static_cast<int>(end(buffer) - d);
        if (dest.rdbuf()->sputn(d, len) != len) dest.setstate(ios_base::badbit);
    }
    return dest;
}

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

bool is_palindrome(const vector<int> &xs) {
    const int n = sz(xs);
    for (int i = 0; i < n / 2; ++i) {
        if (xs[i] != xs[n - 1 - i]) return false;
    }
    return true;
}

ll solve(const lll N) {
    lll result = 1;
    for (lll x = 2; x * x * x <= N; ++x) {
        const auto ds = digits_reversed(x * x * x);
        if (is_palindrome(ds)) {
            result = x * x * x;
        }
    }
    return static_cast<ll>(result);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N;
    cin >> N;
    cout << solve(N) << '\n';
}
