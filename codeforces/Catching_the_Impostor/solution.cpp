#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> xs(k, 0);
    for (auto &x : xs) cin >> x;

    set<int> xss(cbegin(xs), cend(xs));
    const int verified = xss.size();

    bool ans = verified == n - 1;
    cout << (ans ? "YES\n" : "NO\n");

    return 0;
}
