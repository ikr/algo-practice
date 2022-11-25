#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mod = 1'000'000'007;
struct Mod {
    ll x;
    Mod(ll xx) : x(xx) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
    Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
    Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

static constexpr int SZ = 100002;

vector<Mod> precompute_complimentary() {
    vector<Mod> result(SZ, 0);
    result[1] = 0;
    result[2] = 1;

    for (int i = 3; i < SZ; ++i) {
        result[i] = Mod{i - 1} * (result[i - 1] + result[i - 2]);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<Mod> fact(SZ, 1);
    for (int i = 2; i < SZ; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    const auto compli = precompute_complimentary();

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        cout << (fact[N] - compli[N]).x << '\n';
    }

    return 0;
}
