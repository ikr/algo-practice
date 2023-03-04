#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<int> ye(N, 0);
    vector<bool> re(N, false);

    while (Q--) {
        int cmd, x;
        cin >> cmd >> x;
        --x;

        if (cmd == 1) {
            ++ye[x];
        } else if (cmd == 2) {
            re[x] = true;
        } else {
            assert(cmd == 3);
            const auto removed = ye[x] >= 2 || re[x];
            cout << (removed ? "Yes" : "No") << '\n';
        }
    }

    return 0;
}
