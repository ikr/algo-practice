#include <bits/stdc++.h>
using namespace std;

unordered_set<int> distinct_distances(const vector<int> &xs) {
    const int n = xs.size();
    unordered_set<int> ans;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (xs[i] != xs[j]) ans.insert(xs[j] - xs[i]);
        }
    }
    return ans;
}

pair<int, unordered_set<int>> intersect(unordered_set<int> xs,
                                        const unordered_set<int> &ys) {
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
    const unordered_set<int> present(cbegin(ys), cend(ys));

    const auto [common, unpaired] =
        intersect(distinct_distances(xs), distinct_distances(ys));

    int win = 0;

    for (int i = 0; i <= H; ++i) {
        unordered_set<int> ds;

        for (const int y : ys) {
            if (present.count(i)) continue;
            const int curr = abs(i - y);
            if (!unpaired.count(curr)) continue;
            ds.insert(curr);
        }

        win = max(win, static_cast<int>(ds.size()));
    }

    return common + win;
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
