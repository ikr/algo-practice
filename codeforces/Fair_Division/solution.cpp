#include <bits/stdc++.h>
using namespace std;

bool possible(const vector<int> &xs) {
    const int total = accumulate(cbegin(xs), cend(xs), 0);
    if (total % 2) return false;

    const bool some_ones = any_of(cbegin(xs), cend(xs), [](const int x) { return x == 1; });
    return ((total / 2) % 2) ? some_ones : true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
