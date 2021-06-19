#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// https://www.geeksforgeeks.org/least-prime-factor-of-numbers-till-n/
vi least_prime_factor(int n) {
    // Create a vector to store least primes.
    // Initialize all entries as 0.
    vector<int> ans(n + 1, 0);

    // We need to print 1 for 1.
    ans[1] = 1;

    for (int i = 2; i <= n; i++) {
        // least_prime[i] == 0
        // means it i is prime
        if (ans[i] == 0) {
            // marking the prime number
            // as its own lpf
            ans[i] = i;

            // mark it as a divisor for all its
            // multiples if not already marked
            for (ll j = llof(i) * i; j <= llof(n); j += i)
                if (ans[j] == 0) ans[j] = i;
        }
    }

    return ans;
}

ll proper_pairs_num(const int l, const int r) {
    const auto lpf = least_prime_factor(r);
    ll ans = 0;
    set<int> seen;

    for (int i = l; i <= r; ++i) {
        const int p = lpf[i];
        if (p == i || seen.count(p)) continue;

        const int d = r - i + 1;
        const ll k = d / p + 1 - d / i;
        ans += k * (k - 1);
        seen.insert(p);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int l, r;
    cin >> l >> r;

    cout << proper_pairs_num(l, r) << '\n';
    return 0;
}
