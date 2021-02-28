#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr bool intersect(const pii ab, const pii cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    return !(b < c || d < a);
}

int intersection_length(const pii ab, const pii cd) {
    array<int, 4> xs{ab.first, ab.second, cd.first, cd.second};
    sort(begin(xs), end(xs));
    return xs[2] - xs[1];
}

int total_overlap(const vector<pii> &a_segs, const vector<pii> &b_segs,
                  const vector<int> &es) {
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> es;
        es.reserve(n + m);

        vector<pii> a_segs(n);
        for (auto &[l, r] : a_segs) {
            cin >> l >> r;
            es.push_back(l);
            es.push_back(r);
        }

        vector<pii> b_segs(n);
        for (auto &[l, r] : b_segs) {
            cin >> l >> r;
            es.push_back(l);
            es.push_back(r);
        }

        sort(begin(es), end(es));
        es.erase(unique(begin(es), end(es)), cend(es));

        cout << total_overlap(a_segs, b_segs, es) << '\n';
    }

    return 0;
}
