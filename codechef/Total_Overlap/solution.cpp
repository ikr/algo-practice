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

map<int, int> gather_indices_by_values(const vector<int> &es) {
    const int n = es.size();
    map<int, int> ans;
    for (int i = 0; i < n; ++i) ans[es[i]] = i;
    return ans;
}

vector<int> build_difference_array(const vector<pii> &segs,
                                   const map<int, int> &idx) {
    const int n = idx.size();
    vector<int> ans(n + 1, 0);

    for (const auto [l, r] : segs) {
        ++ans[idx.at(l)];
        --ans[idx.at(r) + 1];
    }

    return ans;
}

long long total_overlap(const vector<pii> &a_segs, const vector<pii> &b_segs,
                        const vector<int> &es) {
    const auto idx = gather_indices_by_values(es);
    const auto da = build_difference_array(a_segs, idx);
    const auto db = build_difference_array(b_segs, idx);

    const int n = es.size();
    int x = da[0];
    int y = db[0];
    long long ans = 0;

    for (int i = 1; i < n; ++i) {
        x += da[i - 1];
        y += db[i - 1];

        ans += x * y * (es[i] - es[i - 1]);
    }

    return ans;
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
