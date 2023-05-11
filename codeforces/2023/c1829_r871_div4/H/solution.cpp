#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint num_seq_z(const vector<int> &xs) {
    const auto n = sz(xs);

    vector<int> freq(64, 0);
    for (const auto x : xs) ++freq[x];

    mint ans{};

    for (const auto x : xs) {
        for (int bits = 0; bits < 64; ++bits) {
            if (bits != x && (bits & x) == 0) {
                const auto s = freq[bits];
                ans += s * mint{2}.pow(n - s - 1);
            }
        }
    }

    return ans;
}

mint num_seqs(const vector<int> &xs, const int k) {
    if (!k) return num_seq_z(xs);

    vector<int> fexa;
    vector<int> fsup;

    for (int bits = 0; bits < 64; ++bits) {
        if (__popcount(bits) != k) continue;

        int e{};
        int s{};
        for (const auto x : xs) {
            if (x == bits) {
                ++e;
            } else if ((x & bits) == bits) {
                ++s;
            }
        }

        fexa.push_back(e);
        fsup.push_back(s);
    }

    mint ans = 0;
    for (int i = 0; i < sz(fexa); ++i) {
        ans += (mint{2}.pow(fexa[i]) - 1) * mint{2}.pow(fsup[i]);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << num_seqs(xs, k).val() << '\n';
    }

    return 0;
}
