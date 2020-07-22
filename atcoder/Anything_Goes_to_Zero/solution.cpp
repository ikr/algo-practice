#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;

vi f_table(const int lim) {
    vi ans(lim + 1, 1);
    ans[0] = 0;

    for (int i = 3; i <= lim; ++i) {
        const int p = __builtin_popcount(i);
        ans[i] = 1 + ans[i % p];
    }

    return ans;
}

int two_exp_mod(const int power, const int m) {
    if (!power) return 1;
    if (power % 2) return (2 * two_exp_mod(power - 1, m)) % m;

    const ll sq = two_exp_mod(power / 2, m);
    return (sq * sq) % m;
}

int big_bin_mod(const string &bits, const int m) {
    const int sz = bits.size();
    int ans = 0;

    for (auto it = bits.crbegin(); it != bits.crend(); ++it) {
        if (*it == '0') continue;
        const int i = distance(bits.crbegin(), it);
        assert(i >= 0 && i < sz);

        ans = (ans + two_exp_mod(i, m)) % m;
    }

    return ans;
}

vi f_xi_values(const string &bits) {
    const int sz = bits.size();
    const int ones = count(bits.cbegin(), bits.cend(), '1');
    const vi ys = f_table(1e5 + 1);
    const int a = (ones <= 1) ? 0 : big_bin_mod(bits, ones - 1);
    const int b = big_bin_mod(bits, ones + 1);

    vi ans(sz, 0);

    for (int power = sz - 1; power >= 0; --power) {
        const int i = sz - 1 - power;

        if (bits[i] == '1' && ones != 1) {
            const int m = ones - 1;
            ans[i] = 1 + ys[(a - two_exp_mod(power, m) + m) % m];
        } else if (bits[i] == '0') {
            const int m = ones + 1;
            ans[i] = 1 + ys[(b + two_exp_mod(power, m) + m) % m];
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    string bits;
    cin >> bits;
    assert(static_cast<int>(bits.size()) == sz);

    for (const auto y : f_xi_values(bits)) {
        cout << y << '\n';
    }

    return 0;
}
