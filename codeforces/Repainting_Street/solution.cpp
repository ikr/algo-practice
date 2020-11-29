#include <bits/stdc++.h>
using namespace std;

int min_days(const vector<int> &xs, const int k, const int x0) {
    auto it = find_if(cbegin(xs), cend(xs), [x0](const int x) { return x != x0; });
    int ans = it == cend(xs) ? 0 : 1;

    while (distance(it, cend(xs)) > k) {
        advance(it, k);
        it = find_if(it, cend(xs), [x0](const int x) { return x != x0; });
        if (it != cend(xs)) ++ans;
    }

    return ans;
}

int min_days(const vector<int> &xs, const int k) {
    set<int> xss(cbegin(xs), cend(xs));
    if (xss.size() == 1U) return 0;

    int ans = 1e9;

    for (const int x : xs) {
        ans = min(ans, min_days(xs, k, x));
    }

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
        cout << min_days(xs, k) << '\n';
    }

    return 0;
}
