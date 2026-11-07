#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    vector<int> xs(n);
    iota(begin(xs), end(xs), 1);

    while (q--) {
        int k;
        cin >> k;

        reverse(begin(xs), begin(xs) + k);
        transform(begin(xs), begin(xs) + k, begin(xs),
                  [](const int x) { return -x; });
    }

    for (const auto x : xs) {
        cout << x << '\n';
    }

    return 0;
}
