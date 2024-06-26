#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<ll> default_perm(const ll n) {
    vector<ll> result(n);
    iota(begin(result), end(result), 1LL);
    return result;
}

optional<ll> first_divider(const ll n) {
    const auto total = n * (n + 1LL) / 2LL;
    ll result{};
    for (ll p = 2; p * p <= total; ++p) {
        if (total % p == 0LL) {
            result = max(result, p);
            result = max(result, total / p);
        }
    }
    if (!result) return nullopt;
    return result;
}

vector<ll> best_perm(const ll n) {
    if (n == 1LL) return {1};
    const auto p = first_divider(n);
    if (!p) return default_perm(n);

    set<ll> src;
    for (const auto x : default_perm(n)) src.insert(x);

    vector<ll> result;
    result.reserve(n);
    while (!empty(src)) {
        const ll hi = *crbegin(src);
        result.push_back(hi);
        src.erase(hi);

        if (*p - hi > 0 && src.contains(*p - hi)) {
            result.push_back(*p - hi);
            src.erase(*p - hi);
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
        ll n;
        cin >> n;
        cout << best_perm(n) << '\n';
    }

    return 0;
}
