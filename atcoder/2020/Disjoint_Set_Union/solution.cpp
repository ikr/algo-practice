#include "atcoder/dsu.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;
    atcoder::dsu d(N);

    while (Q--) {
        int op, u, v;
        cin >> op >> u >> v;

        if (op) {
            cout << d.same(u, v) << '\n';
        } else {
            d.merge(u, v);
        }
    }

    return 0;
}
