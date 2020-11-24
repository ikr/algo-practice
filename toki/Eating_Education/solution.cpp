#include <bits/stdc++.h>
using namespace std;

int path_moves(const vector<int> &xs, const int m) {
    const int sz = xs.size();
    int ans = 0;
    for (int i = 1; i < sz; ++i) {
        if (xs[i - 1] < xs[i]) {
            ans += xs[i] - xs[i - 1];
        } else {
            ans += m - xs[i - 1] + xs[i];
        }
    }
    return ans;
}

set<int>::const_iterator after_largest_gap(const set<int> &xss) {
    int top_gap = -1;
    auto ans = cbegin(xss);

    for (auto it = next(cbegin(xss)); it != cend(xss); ++it) {
        const auto pit = prev(it);
        const int gap = *it - *pit;
        if (gap > top_gap) {
            top_gap = gap;
            ans = it;
        }
    }

    return ans;
}

int moves(const vector<int> &xs, const int m) {
    set<int> xss(cbegin(xs), cend(xs));
    const int n = xss.size();
    if (n == 1) return 0;

    const auto mid_it = after_largest_gap(xss);
    const vector<int> pa(cbegin(xss), cend(xss));

    vector<int> pb(mid_it, cend(xss));
    pb.reserve(n);
    copy(cbegin(xss), mid_it, back_inserter(pb));

    return min(path_moves(pa, m), path_moves(pb, m));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> xs(n, 0);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    cout << moves(xs, m) << '\n';
    return 0;
}
