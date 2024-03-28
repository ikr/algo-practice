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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_binary_decimal(ll n) {
    while (n) {
        const auto d = inof(n % 10LL);
        if (d != 0 && d != 1) return false;
        n /= 10LL;
    }

    return true;
}

bool is_representable(const vector<ll> &basis, const int bits, ll n) {
    for (int i = sz(basis) - 1; i >= 0; --i) {
        if ((bits & (1LL << i)) == 0) continue;
        while (n % basis[i] == 0) {
            n /= basis[i];
            if (n == 1 || find(cbegin(basis), cend(basis), n) != cend(basis)) {
                return true;
            }
        };
    }

    return false;
}

bool is_representable(const vector<ll> &basis, const ll n) {
    if (is_binary_decimal(n)) return true;
    for (int bits = 1; bits < (1 << sz(basis)); ++bits) {
        if (is_representable(basis, bits, n)) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<ll> basis;
    for (ll i = 2; i <= 1'000LL; ++i) {
        if (is_binary_decimal(i)) basis.push_back(i);
    }
    // cerr << basis << endl;

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << (is_representable(basis, n) ? "YES" : "NO") << '\n';
    }

    return 0;
}
