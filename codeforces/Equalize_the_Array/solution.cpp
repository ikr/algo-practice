#include <bits/stdc++.h>
using namespace std;

vector<int> gather_freqs(const vector<int> &xs) {
    map<int, int> counts_by_x;
    for (const auto x : xs) ++counts_by_x[x];

    vector<int> ans(counts_by_x.size());
    transform(cbegin(counts_by_x), cend(counts_by_x), begin(ans),
              [](const auto v) { return v.second; });
    return ans;
}

int min_removals(const vector<int> &xs) {
    const auto fs = gather_freqs(xs);
    return 0;
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

        cout << min_removals(xs) << '\n';
    }

    return 0;
}
