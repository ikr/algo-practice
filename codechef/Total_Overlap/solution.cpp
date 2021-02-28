#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

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
        --ans[idx.at(r)];
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
    long long ans = x * y * (es[1] - es[0]);

    for (int i = 1; i < n - 1; ++i) {
        x += da[i];
        y += db[i];

        ans += x * y * (es[i + 1] - es[i]);
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
