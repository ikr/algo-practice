#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<int> votes(n, 0);
    vector<vector<int>> backup_indices(n, vector<int>{});

    while (m--) {
        int a, b;
        cin >> a >> b;

        votes[a - 1] += 1;
        backup_indices[a - 1].push_back(b - 1);
    }

    vector<int> idx(n);
    ranges::iota(idx, 0);

    for (int i0 = 0; i0 != n; ++i0) {
        const auto origninal_i0_votes = votes[i0];
        votes[i0] = -1;

        votes[i0] = origninal_i0_votes;
    }

    stable_sort(begin(idx), end(idx), [&votes](const int i, const int j) {
        return votes[i] > votes[j];
    });

    return 0;
}
