#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> cut_out(const pii hw, const pii ab) {
    const auto [h, w] = hw;
    const auto [a, b] = ab;
    assert(a <= h && b <= w);
    assert(!(a == h && b == w));

    if (a == h) return {{h, w - b}};
    if (b == w) return {{h - a, w}};
    return {{h - a, b}, {a, w - b}, {h - a, w - b}};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, H, W;
    cin >> N >> H >> W;

    vector<pii> AB(N);
    for (auto &[a, b] : AB) {
        cin >> a >> b;
    }

    const auto recur = [&](const auto self, const pii hw,
                           const int invbits) -> int {
        const auto [h, w] = hw;
        assert(h > 0 && w > 0);
        if (invbits == 0) return 0;
        const pii wh{w, h};

        for (int i = 0; i < N; ++i) {
            if (invbits & (1 << i)) {
                if (AB[i] == hw || AB[i] == wh) return (1 << i);
            }
        }

        for (int i0 = 0; i0 < N; ++i0) {
            if (invbits & (1 << i0)) {
                auto [a, b] = AB[i0];
                if (!(a <= h && b <= w) && !(b <= h && a <= w)) continue;

                for (int t = 1; t <= 2; ++t) {
                    if (a <= h && b <= w) {
                        auto rest = cut_out(hw, {a, b});
                        sort(begin(rest), end(rest));
                        do {
                            bool ok = true;
                            int used = (1 << i0);
                            int invbits_ = invbits ^ (1 << i0);
                            for (const auto &hw_ : rest) {
                                const auto used_ = self(self, hw_, invbits_);
                                if (!used_) {
                                    ok = false;
                                    break;
                                }
                                used |= used_;
                                invbits_ ^= used_;
                            }
                            if (ok) return used;
                        } while (next_permutation(begin(rest), end(rest)));
                    }
                    if (a == b) break;
                    swap(a, b);
                }
            }
        }

        return 0;
    };

    const bool yes = recur(recur, {H, W}, (1 << N) - 1);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
