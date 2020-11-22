#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll path_moves(const vector<int> &xs, const int m) {
    const int sz = xs.size();
    ll ans = 0;
    for (int i = 1; i < sz; ++i) {
        if (xs[i - 1] < xs[i]) {
            ans += xs[i] - xs[i - 1];
        } else {
            ans += m - xs[i - 1] + xs[i];
        }
    }
    return ans;
}

ll moves(const vector<int> &xs, const int m) {
    set<int> xss(cbegin(xs), cend(xs));
    const int n = xss.size();
    if (n == 1) return 0;

    const int lo = *cbegin(xss);
    const int hi = *crbegin(xss);
    const int mid = lo + (hi - lo) / 2;
    const auto mid_it = xss.upper_bound(mid);

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
