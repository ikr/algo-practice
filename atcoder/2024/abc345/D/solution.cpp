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
                           const vector<pii> &inventory) -> bool {
        const auto [h, w] = hw;
        assert(h > 0 && w > 0);
        if (empty(inventory)) return false;
        const pii wh{w, h};

        if (any_of(cbegin(inventory), cend(inventory),
                   [hw, wh](const pii ab) -> bool {
                       return ab == hw || ab == wh;
                   })) {
            return true;
        }

        for (int i0 = 0; i0 < sz(inventory); ++i0) {
            const auto [a, b] = inventory[i0];
            if (!(a <= h && b <= w) && !(b <= h && a <= w)) continue;

            auto inventory_ = inventory;
            inventory_.erase(cbegin(inventory_) + i0);

            if (a <= h && b <= w) {
                const auto rest = cut_out(hw, {a, b});
                bool ok = true;
            }

            if (b <= h && a <= w) {
            }
        }

        return false;
    };

    return 0;
}
