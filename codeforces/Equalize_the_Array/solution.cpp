#include <bits/stdc++.h>
using namespace std;

vector<int> sorted_freqs(const vector<int> &xs) {
    map<int, int> counts_by_x;
    for (const auto x : xs) ++counts_by_x[x];

    vector<int> ans(counts_by_x.size());
    transform(cbegin(counts_by_x), cend(counts_by_x), begin(ans),
              [](const auto v) { return v.second; });

    sort(begin(ans), end(ans));
    return ans;
}

vector<int> prefix_sums(const vector<int> &xs) {
    vector<int> ans(xs.size());
    partial_sum(cbegin(xs), cend(xs), begin(ans));
    return ans;
}

int min_removals(const vector<int> &xs) {
    const auto fs = sorted_freqs(xs);
    const auto ss = prefix_sums(fs);

    const int n = fs.size();
    int ans = ss.back() - fs[0] * n;

    for (int i = 1; i < n; ++i) {
        const int tail_sz = n - i;
        const int tail_val = ss.back() - ss[i - 1];
        const int candidate = ss[i - 1] + tail_val - fs[i] * tail_sz;

        ans = min(ans, candidate);
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

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_removals(xs) << '\n';
    }

    return 0;
}
