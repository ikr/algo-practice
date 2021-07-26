#include <bits/stdc++.h>
using namespace std;
static constexpr int INF = 1e9 + 111;

int dominant_index(const vector<int> &xs) {
    unordered_set<int> xss(cbegin(xs), cend(xs));
    if (xss.size() == 1) return -1;

    const int top = *max_element(cbegin(xs), cend(xs));
    const int n = xs.size();
    for (int i = 0; i < n; ++i) {
        if (xs[i] != top) continue;

        const int l = i == 0 ? INF : xs[i - 1];
        const int r = i == n - 1 ? INF : xs[i + 1];
        if (l < xs[i] || r < xs[i]) return i + 1;
    }

    assert(false && "must not be possible");
    return -1;
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

        cout << dominant_index(xs) << '\n';
    }

    return 0;
}
