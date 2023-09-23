#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int Q, K;
    cin >> Q >> K;

    vector<vector<mint>> T(Q, vector<mint>(K + 1, 0));
    vector<vector<mint>> P(Q, vector<mint>(K + 1, 0));
    vector<int> inventory;
    inventory.reserve(Q / 2 + 1);
    unordered_set<int> deleted_indices;

    const auto index_to_delete = [&](const int x) -> int {
        for (int i = 0; i < sz(inventory); ++i) {
            if (inventory[i] == x && !deleted_indices.contains(i)) return i;
        }
        assert(false && "ouch!");
        return -1;
    };

    for (int q = 0; q < Q; ++q) {
        char op;
        int x;
        cin >> op >> x;

        if (op == '+') {
            for (int i = 0; i < sz(inventory); ++i) {
                if (deleted_indices.contains(i)) continue;
            }

            inventory.push_back(x);
        } else {
            assert(op == '-');
            deleted_indices.insert(index_to_delete(x));
            const auto m = sz(inventory);
        }
    }

    return 0;
}
