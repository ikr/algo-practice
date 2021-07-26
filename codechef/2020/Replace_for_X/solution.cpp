#include <bits/stdc++.h>
using namespace std;

int min_ops(vector<int> &xs, const int X, const int p, const int k) {
    partial_sort(begin(xs), begin(xs) + p, end(xs));
    if (xs[p - 1] == X) return 0;

    if (xs[p - 1] > X) {
        if (k < p) return -1;

        return count_if(cbegin(xs), cbegin(xs) + p,
                        [X](const int x) { return x > X; });
    }

    if (k > p) return -1;

    return count_if(cbegin(xs) + p - 1, cend(xs),
                    [X](const int x) { return x < X; });
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
