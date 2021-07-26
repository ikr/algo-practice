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

static constexpr ll B9 = 111'111'111;
static constexpr ll B7 = 1'111'111;
static constexpr ll B5 = 11'111;
static constexpr ll B3 = 111;

using Coeffs = array<ll, 4>;

array<vector<Coeffs>, 11> coeffs_by_mod() {
    array<vector<Coeffs>, 11> ans{};

    for (int k9 = 0; k9 <= 10; ++k9) {
        for (int k7 = 0; k7 <= 10; ++k7) {
            for (int k5 = 0; k5 <= 10; ++k5) {
                for (int k3 = 0; k3 <= 10; ++k3) {
                    const int r = k9 + k7 + k5 + k3;
                    if (!r || r > 10) continue;

                    ans[r].push_back(Coeffs{k9, k7, k5, k3});
                }
            }
        }
    }

    return ans;
}

vll combos(const array<vector<Coeffs>, 11> &cbm, const ll x) {
    const auto r = x % 11LL;

    vll ans;
    for (const auto &coeff : cbm[r]) {
        const auto y =
            B9 * coeff[0] + B7 * coeff[1] + B5 * coeff[2] + B3 * coeff[3];
        if (y <= x) ans.push_back(y);
    }
    return ans;
}

bool possible(const array<vector<Coeffs>, 11> &cbm, const ll x) {
    const auto r = x % 11LL;
    if (r == 0) return true;

    for (const auto y : combos(cbm, x)) {
        if ((x - y) % 11 == 0) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto cbm = coeffs_by_mod();

    int t;
    cin >> t;
    while (t--) {
        ll x;
        cin >> x;
        cout << (possible(cbm, x) ? "YES\n" : "NO\n");
    }

    return 0;
}
