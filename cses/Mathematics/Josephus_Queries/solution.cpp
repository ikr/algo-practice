#include <bits/stdc++.h>
using namespace std;

int div_ceil(const int numerator, const int denominator) {
    const int q = numerator / denominator;
    return (numerator % denominator) ? (q + 1) : q;
}

enum class Start { ZERO, ONE };

struct Circle final {
    int round_index;
    int lo;
    int hi;
    int num;
    Start start_index;

    int delta() const { return round_index * 2; }
    int child_at(const int index) const { return lo + delta() * index; }

    bool is_reached_this_round(const int index) const {
        return child_at(index) <= hi;
    }

    int num_removed_this_round() const {
        return start_index == Start::ZERO ? div_ceil(num, 2) : num / 2;
    }
};

int kth_child_removed(const int n, int k) {
    Circle ci{0, 1, n, n, Start::ONE};

    while (!ci.is_reached_this_round(k)) {
        const int d = ci.num_removed_this_round();
        ci = Circle{ci.round_index + 1, };
    }

    return ci.child_at(ci.start_index == Start::ZERO ? k : k + 1);
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
