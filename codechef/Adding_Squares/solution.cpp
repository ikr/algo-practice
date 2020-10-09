#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

set<int> distinct_distances(const vector<int> &xs) {
    const int n = xs.size();
    set<int> ans;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (xs[i] != xs[j]) ans.insert(abs(xs[i] - xs[j]));
        }
    }
    return ans;
}

pair<int, set<int>> intersect(set<int> xs, const set<int> &ys) {
    int common_count = 0;
    for (auto it = cbegin(xs); it != cend(xs);) {
        if (ys.count(*it)) {
            it = xs.erase(it);
            ++common_count;
        } else {
            ++it;
        }
    }
    return {common_count, xs};
}

int max_sq_num(const vector<int> &xs, const vector<int> &ys, const int H) {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int W, H, N, M;
    cin >> W >> H >> N >> M;

    vector<int> xs(N, 0);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    vector<int> ys(M, 0);
    for (auto &y : ys) cin >> y;
    sort(begin(ys), end(ys));

    cout << max_sq_num(xs, ys, H) << '\n';
    return 0;
}
