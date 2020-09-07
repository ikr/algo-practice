#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
static constexpr int BIT_MAX = 59; // log2(1e18)

vector<int> gather_bits_freq(const vector<ull> &xs) {
    vector<int> ans(BIT_MAX + 1, 0);

    for (const ull x : xs) {
        bitset<BIT_MAX + 1> bits{x};
        for (int i = 0; i <= BIT_MAX; ++i) {
            if (bits[i]) ++ans[i];
        }
    }

    return ans;
}

int highest_set_bit_with_even_freq(const vector<int> &bits_freq) {
    for (int i = BIT_MAX; i >= 0; --i) {
        if (bits_freq[i] && (bits_freq[i] % 2 == 0)) return i;
    }

    return -1;
}

ull max_xor(const vector<ull> &xs) {
    const int hi = highest_set_bit_with_even_freq(gather_bits_freq(xs));
    const ull s = accumulate(xs.cbegin() + 1, xs.cend(), xs[0], bit_xor<ull>{});
    if (hi == -1) return s;
    const ull mask = (1ULL << (hi + 1)) - 1ULL;
    return s | mask;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<ull> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << max_xor(xs) << '\n';
    return 0;
}
