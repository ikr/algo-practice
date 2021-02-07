#include <bits/stdc++.h>
using namespace std;

int div_ceil(const int numerator, const int denominator) {
    const int q = numerator / denominator;
    return (numerator % denominator) ? (q + 1) : q;
}

struct Circle final {
    int front;
    int delta;
    int size;

    int back() const { return front + delta * (size - 1); }
    int kth_removed(const int k) const { return front + (2 * k + 1) * delta; }
    int third() const { return front + 2 * delta; }

    int removed_this_round() const {
        return (size % 2) ? size / 2 + 1 : size / 2;
    }

    Circle next_round() const {
        const bool odd = size % 2;
        return {odd ? third() : front, 2 * delta, size - removed_this_round()};
    }
};

int kth_child_removed(const int n, int k) {
    Circle ci{1, 1, n};

    while (ci.kth_removed(k) > ci.back()) {
        const bool odd = ci.size % 2;
        if (odd && ci.size / 2 + 1 == k) return ci.front;

        k -= ci.removed_this_round();
        ci = ci.next_round();
    }

    return ci.kth_removed(k);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        --k;
        cout << kth_child_removed(n, k) << '\n';
    }

    return 0;
}
