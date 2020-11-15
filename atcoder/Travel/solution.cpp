#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gather_distance(const vector<vector<int>> &dist, const vector<int> &seq) {
    ll ans = dist[0][seq[0]];
    const int sz = seq.size();

    for (int i = 0; i < sz - 1; ++i) {
        ans += dist[seq[i]][seq[i + 1]];
    }

    ans += dist[seq.back()][0];

    return ans;
}

int solve(const vector<vector<int>> &dist, const int k) {
    const int n = dist.size();
    vector<int> seq(n - 1, 0);
    iota(begin(seq), end(seq), 1);

    int ans = 0;
    do {
        const ll d = gather_distance(dist, seq);
        if (d == k) ++ans;
    } while (std::next_permutation(seq.begin(), seq.end()));

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> rows(n, vector<int>(n, 0));
    for (auto &row : rows) {
        for (auto &d : row) cin >> d;
    }

    cout << solve(rows, k) << '\n';

    return 0;
}
