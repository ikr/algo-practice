#include <bits/stdc++.h>
using namespace std;

int count_sources(const int n, const unordered_multimap<int, int> &ins) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (ins.count(i) == 0) ++ans;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        unordered_multimap<int, int> ins;

        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            ins.emplace(v - 1, u - 1);
        }

        cout << (count_sources(n, ins) - 1) << '\n';
    }

    return 0;
}
