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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

ll mutually_prime_pairs_num_bruteforce(const int l, const int r) {
    ll ans = 0;
    for (ll i = l; i <= r - 1; ++i) {
        for (ll j = i + 1; j <= r; ++j) {
            if (gcd(i, j) == 1) ++ans;
        }
    }
    return ans;
}

vi precalculate_phi(const int LIM) {
    vi phi(LIM, 0);

    for (int i = 0; i < LIM; ++i) phi[i] = i & 1 ? i : i / 2;

    for (int i = 3; i < LIM; i += 2) {
        if (phi[i] == i) {
            for (int j = i; j < LIM; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }

    return phi;
}

ll mutually_prime_pairs_num(const vi &phi, const int l, const int r) {
    ll ans = 0;

    for (int i = l; i <= r; ++i) {
        ans += phi[r] - phi[l - 1];
    }

    --ans;
    return ans;
}

ll proper_pairs_num(const int l, const int r) {
    const auto phi = precalculate_phi(r + 1);
    cerr << mutually_prime_pairs_num_bruteforce(l, r) << " / "
         << mutually_prime_pairs_num(phi, l, r) << endl;
    return -1;
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
