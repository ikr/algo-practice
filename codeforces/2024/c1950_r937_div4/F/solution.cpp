#include <bits/stdc++.h>
using namespace std;

constexpr int mlog2(const int x) {
    return 8 * sizeof(int) - __builtin_clz(x) - 1;
}

namespace complete_bintree {
constexpr int largest_contained_a0(const int a) {
    assert(a > 0);
    int shift{1};
    while ((1 << (shift + 1)) - 1 <= a) ++shift;
    return (1 << shift) - 1;
}

constexpr int height(const int a) { return mlog2(a + 1); }
} // namespace complete_bintree

namespace cbt = complete_bintree;

int min_tree_height(const int a, int b, const int c) {
    if (!a) return c == 1 ? b : -1;

    const auto a0 = cbt::largest_contained_a0(a);
    const auto slots = a0 + 1;
    const auto ra = a - a0;
    assert(ra >= 0);

    const auto slots_l = ra * 2;
    const auto slots_r = slots - ra;
    assert(slots_r > 0);
    if (slots_l + slots_r != c) return -1;

    const auto h0 = cbt::height(a0);
    set<int> pq;
    for (int i = 0; i < slots_l; ++i) pq.insert(h0 + 1);
    for (int i = 0; i < slots_r; ++i) pq.insert(h0);
    assert(!empty(pq));

    while (b) {
        const auto cur = *cbegin(pq);
        pq.erase(cbegin(pq));
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
