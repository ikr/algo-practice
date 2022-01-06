#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr ll neq(const ll a, const ll b) { return a == b ? 0 : 1; }

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

ll the_z(const vi &ds) {
    assert(sz(ds) == 14);

    ll z = ds[0] + 1; // 01
    z *= 26;
    z += ds[1] + 9; // 02
    z *= 26;
    z += ds[2] + 11; // 03

    {
        const auto x = neq((z % 26LL) - 13, ds[3]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[3] + 6) * x;
    } // 04

    z *= 26;
    z += ds[4] + 6; // 05
    z *= 26;
    z += ds[5] + 13; // 06

    {
        const auto x = neq((z % 26LL) - 14, ds[6]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[6] + 13) * x;
    } // 07

    z *= 26;
    z += ds[7] + 5; // 08

    {
        const auto x = neq((z % 26LL) - 8, ds[8]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[8] + 7) * x;
    } // 09

    z *= 26;
    z += ds[9] + 2; // 10

    {
        const auto x = neq((z % 26LL) - 9, ds[10]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[10] + 10) * x;
    } // 11

    {
        const auto x = neq((z % 26LL) - 11, ds[11]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[11] + 14) * x;
    } // 12

    {
        const auto x = neq((z % 26LL) - 6, ds[12]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[12] + 7) * x;
    } // 13

    {
        const auto x = neq((z % 26LL) - 5, ds[13]);
        z /= 26LL;
        z *= 25 * x + 1;
        z += (ds[13] + 1) * x;
    } // 14

    return z;
}

template <typename T> T number(const vi &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

int main() {
    cerr << the_z({1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1, 2, 3, 4}) << endl;
    return 0;
}
