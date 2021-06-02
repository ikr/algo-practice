#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

vector<bool> sieve(const int n) {
    vector<bool> ans(n + 1, true);
    ans[0] = false;
    ans[1] = false;

    for (int i = 2; i <= n; ++i) {
        if (!ans[i]) continue;
        if (llof(i) * i > llof(n)) continue;

        for (int j = i * i; j <= n; j += i) {
            ans[j] = false;
        }
    }

    return ans;
}

vi primes(const vector<bool> &s) {
    vi ans;
    ans.reserve(sz(s) / 2);

    for (int i = 0; i < sz(s); ++i) {
        if (s[i]) ans.push_back(i);
    }

    return ans;
}

vi prime_pair_products(const vi &ps, const int n) {
    vi ans;
    ans.reserve(sz(ps));

    for (int i = 0; llof(ps[i]) * ps[i + 1] <= llof(n); ++i) {
        for (int j = i + 1; j < sz(ps); ++j) {
            if (llof(ps[i]) * ps[j] > llof(n)) break;
            ans.push_back(ps[i] * ps[j]);
        }
    }

    sort(begin(ans), end(ans));
    return ans;
}

static constexpr int LIM = 100;

int components_num(const vi &ps, const vi &pps, const int n) {
    if (n > LIM) return 1;

    const auto it = upper_bound(cbegin(ps), cend(ps), n);
    const int a = inof(distance(cbegin(ps), it));

    const auto jt = upper_bound(cbegin(pps), cend(pps), n);
    const int b = inof(distance(cbegin(pps), jt));

    return max(1, a - b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto ps = primes(sieve(LIM));
    const auto pps = prime_pair_products(ps, LIM);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << components_num(ps, pps, n) << '\n';
    }

    return 0;
}
