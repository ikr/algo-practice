#include <bits/stdc++.h>
using namespace std;

struct State final {
    int round_index;
    int lo;
    int hi;
    int start_index;

    int delta() const { return round_index * 2; }

    int child_in_this_round(const int index) const {
        return lo + delta() * index;
    }

    bool is_reached_this_round(const int index) const {
        return child_in_this_round(index) <= hi;
    }
};

int kth_child_removed(const int n, const int k) { return 0; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << kth_child_removed(n, k) << '\n';
    }

    return 0;
}
