#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int Q;
    cin >> Q;

    set<pii> xs;

    for (int i = 1; i <= Q; ++i) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int x;
            cin >> x;

            const auto it = xs.lower_bound(pii{x, 0});
            if (it == cend(xs) || it->first != x) {
                xs.emplace(x, 1);
            } else {
                const auto c = it->second;
                xs.erase(it);
                xs.emplace(x, c + 1);
            }
        } else if (cmd == 2) {
            int x, dc;
            cin >> x >> dc;

            const auto it = xs.lower_bound(pii{x, 0});
            if (it != cend(xs) && it->first == x) {
                auto c = it->second;
                xs.erase(it);
                c = max(0, c - dc);
                if (c) xs.emplace(x, c);
            }

        } else {
            assert(cmd == 3);
            const auto lo = cbegin(xs)->first;
            const auto hi = crbegin(xs)->first;
            cout << (hi - lo) << '\n';
        }
    }

    return 0;
}
