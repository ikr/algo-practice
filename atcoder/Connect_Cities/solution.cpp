#include "atcoder/scc.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    atcoder::scc_graph g(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g.add_edge(u, v);
        g.add_edge(v, u);
    }

    cout << (g.scc().size() - 1) << '\n';

    return 0;
}
