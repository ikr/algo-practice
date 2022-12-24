#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    int Q;
    cin >> Q;

    for (int q = 1; q <= Q; ++q) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int k;
            cin >> k;
            --k;

            int x;
            cin >> x;
            xs[k] = x;
        } else {
            assert(cmd == 2);
            int k;
            cin >> k;
            --k;

            cout << xs[k] << '\n';
        }
    }

    return 0;
}
