#include <bits/stdc++.h>
using namespace std;

pair<int, int> ijth(vector<int> xs, const int i, const int j) {
    const int n = xs.size();
    assert(i < n);
    assert(i >= 0);
    assert(j < n);
    assert(j >= 0);

    partial_sort(begin(xs), begin(xs) + max(i, j), end(xs));
    return {xs[i], xs[j]};
}

int min_ops(const vector<int> &xs, const int X, const int p, const int k) {
    const auto [px, kx] = ijth(xs, p, k);
    if (px == X) return 0;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int N, X, p, k;
        cin >> N >> X >> p >> k;

        vector<int> xs(N, 0);
        for (auto &x : xs) cin >> x;
        cout << min_ops(xs, X, p, k) << '\n';
    }

    return 0;
}
