#include <bits/stdc++.h>
using namespace std;

int rights(const int k, const vector<int> &xs, const int i) {
    const int n = xs.size();
    assert(i >= 0);
    assert(i < n);
    int lo = 1;
    int hi = n - i;

    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        assert(i + mid - 1 >= 0);
        assert(i + mid - 1 < n);

        if (xs[i + mid - 1] > xs[i] + k)
            hi = mid - 1;
        else
            lo = mid + 1;

        cout << "lo:" << lo << " mid:" << mid << " hi:" << hi << endl;
    }

    return lo;
}

int max_saved(const int k, const vector<int> &xs) {
    const int n = xs.size();
    return n;
}

void test_stuff() {
    vector<int> xs{1, 1, 2, 3, 4, 5, 5, 10};
    assert(rights(1, xs, 0) == 3);

    const int res = rights(1, xs, 1);
    cout << "→ " << res << endl;
    assert(rights(1, xs, 1) == 2);
    assert(rights(1, xs, 2) == 2);
    assert(rights(1, xs, 3) == 2);
    assert(rights(1, xs, 4) == 3);
    assert(rights(1, xs, 5) == 2);
    assert(rights(1, xs, 6) == 1);
    assert(rights(1, xs, 7) == 1);
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
        sort(begin(xs), end(xs));

        for (int i = 0; i < n; ++i) {
            int y;
            cin >> y;
        }

        cout << max_saved(k, xs) << '\n';
    }

    test_stuff();
    return 0;
}
