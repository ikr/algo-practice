#include <bits/stdc++.h>
using namespace std;

int min_tree_height(const int a, int b, const int c) {
    if (!a) return c == 1 ? b : -1;

    auto h0 = 0;
    while ((1 << (h0 + 1)) - 1 <= a) ++h0;

    const auto l0 = 1 << h0;
    const auto a0 = l0 - 1;
    assert(a0 <= a);
    const auto ra = a0 - a;

    auto leaves_l = ra * 2;
    auto leaves_r = l0 - ra;
    assert(leaves_r > 0);
    if (c != leaves_l + leaves_r) return -1;

    set<int> pq;
    for (int i = 0; i < leaves_l; ++i) pq.insert(h0 + 1);
    for (int i = 0; i < leaves_r; ++i) pq.insert(h0);
    assert(!empty(pq));

    while (b) {
        const auto cur = *cbegin(pq);
        pq.insert(cur + 1);
        --b;
    }

    return *crbegin(pq);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << min_tree_height(a, b, c) << '\n';
    }

    return 0;
}
