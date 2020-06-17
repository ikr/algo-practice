#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int min_moves(const vi &xs) {
    const int sz = xs.size();
    int even = 0;
    int odd = 0;
    int misplaced = 0;

    for (int i = 0; i != sz; ++i) {
        if (xs[i] % 2) ++odd;
        else ++even;
        if (xs[i] % 2 != i %2) ++misplaced;
    }

    if (sz % 2) {
        if (even != sz / 2 + 1 || odd != sz / 2) return -1;
    } else {
        if (even != sz / 2 || odd != sz / 2) return -1;
    }

    return misplaced / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;
        vi xs(sz, 0);
        for (auto &x : xs) cin >> x;
        cout << min_moves(xs) << '\n';
    }

    return 0;
}
