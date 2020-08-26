#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> gather_counts(const vector<int> &xs) {
    vector<int> ans(4, 0);
    for (const auto x : xs) ++ans[x];
    return {ans[1], ans[2], ans[3]};
}

double expected_operations_count(const vector<int> &xs) {
    const int n = xs.size();

    vector<vector<vector<double>>> memo(
        n + 1, vector<vector<double>>(n + 1, vector<double>(n + 1, -1)));
    memo[0][0][0] = 0.0;

    function<double(int, int, int)> recur;

    recur = [&recur, &memo, n](const int i, const int j, const int k) {
        if (i < 0 || j < 0 || k < 0) return 0.0;

        if (memo[i][j][k] < 0) {
            memo[i][j][k] =
                (n + i * recur(i - 1, j, k) + j * recur(i + 1, j - 1, k) +
                 k * recur(i, j + 1, k - 1)) /
                (i + j + k);
        }

        return memo[i][j][k];
    };

    const auto [ones, twos, threes] = gather_counts(xs);
    return recur(ones, twos, threes);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz = 0;
    cin >> sz;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout.precision(17);
    cout << expected_operations_count(xs) << '\n';

    return 0;
}
