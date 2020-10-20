#include <bits/stdc++.h>
using namespace std;

int shifts(const vector<int> &xs) {
    if (find(cbegin(xs), cend(xs), 1) == cend(xs)) return 0;

    const int n = xs.size();
    int lo = 0;
    while (xs[lo] != 1) ++lo;
    int hi = n - 1;
    while (xs[hi] != 1) --hi;

    return count(cbegin(xs) + lo, cbegin(xs) + hi, 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << shifts(xs) << '\n';
    }

    return 0;
}
