#include <bits/stdc++.h>
using namespace std;

int trips(const vector<int> &xs, const int k) {
    if (*max_element(cbegin(xs), cend(xs)) > k) return -1;

    int ans = 0;
    int capacity = k;

    for (const auto x : xs) {
        if (capacity > x) {
            capacity -= x;
            continue;
        }

        if (capacity == x) {
            ++ans;
            capacity = k;
            continue;
        }

        assert(capacity < x);
        ++ans;

        capacity = k - x;
        if (capacity == 0) {
            capacity = k;
            ++ans;
        }
    }

    if (capacity < k) ++ans;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        cout << trips(xs, k) << '\n';
    }

    return 0;
}
