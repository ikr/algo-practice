#include <bits/stdc++.h>
using namespace std;

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

vi digits_reversed(ll n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % 10LL));
        n /= 10;
    }

    return ans;
}

vi digits(const ll n) {
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

int min_k(const ll n) {
    if (n == 0) return 0;
    if (n <= 3) return 1;

    const auto ds = digits(n);

    vi lo(sz(ds), 0);
    for (int i = 0; i < sz(ds); ++i) {
        if (ds[i] == 0) {
            assert(i > 0);

            if (lo[i - 1] == ds[i - 1]) {
                --lo[i - 1];
            }

            lo[i] = 3;
            continue;
        }

        if (i > 0 && lo[i - 1] < ds[i - 1]) {
            lo[i] = 3;
            continue;
        }

        lo[i] = min(3, ds[i]);
    }

    return 1 + min_k(n - number(lo));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        cout << min_k(n) << '\n';
    }

    return 0;
}
