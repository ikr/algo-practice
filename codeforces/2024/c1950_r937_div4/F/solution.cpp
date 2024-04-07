#include <bits/stdc++.h>
using namespace std;

static constexpr int Inf = 1'000'000'000;

constexpr int mlog2(const int x) {
    return 8 * sizeof(int) - __builtin_clz(x) - 1;
}

constexpr int complete_bintre_height(const int a) { return mlog2(a + 1); }

constexpr int largest_contained_a0(const int a) {
    assert(a > 0);
    int shift{1};
    while ((1 << (shift + 1)) - 1 <= a) ++shift;
    return (1 << shift) - 1;
}

int min_tree_height(const int a, const int a0, const int b, const int c) {
    assert(a0 <= a);
    assert(__builtin_popcount(a0 + 1) == 1);

    multiset<int> pq;
    for (int i = 0; i <= a0; ++i) pq.insert(complete_bintre_height(a0));

    const auto is_largest_a0 = a0 == largest_contained_a0(a);
    assert(!empty(pq));
    for (int i = 0; i < a - a0; ++i) {
        const auto it = is_largest_a0 ? cbegin(pq) : prev(cend(pq));
        const auto h = *it;
        pq.erase(it);
        pq.insert(h + 1);
        pq.insert(h + 1);
    }
    if (ssize(pq) != c) return Inf;

    for (int i = 0; i < b; ++i) {
        const auto cur = *cbegin(pq);
        pq.erase(cbegin(pq));
        pq.insert(cur + 1);
    }

    return *crbegin(pq);
}

int min_tree_height(const int a, int b, const int c) {
    if (!a) return c == 1 ? b : Inf;

    int result{Inf};
    for (int shift = 1; (1 << shift) - 1 <= a; ++shift) {
        result = min(result, min_tree_height(a, (1 << shift) - 1, b, c));
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        const auto result = min_tree_height(a, b, c);
        cout << (result == Inf ? -1 : result) << '\n';
    }

    return 0;
}
