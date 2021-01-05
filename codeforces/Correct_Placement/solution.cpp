#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> in_fronts(vector<pair<int, int>> fs) {
    const int n = fs.size();

    vector<int> idx_a(n);
    iota(begin(idx_a), end(idx_a), 0);
    sort(begin(idx_a), end(idx_a),
         [&](const auto lhs, const auto rhs) { return fs[lhs] > fs[rhs]; });

    vector<int> idx_b(n);
    iota(begin(idx_b), end(idx_b), 0);
    sort(begin(idx_b), end(idx_b), [&](const auto lhs, const auto rhs) {
        const auto [a, b] = fs[lhs];
        const auto [x, y] = fs[rhs];
        return pair{b, a} > pair{y, x};
    });

    vector<int> ans(n, -1);

    for (int i = 0; i < n; ++i) {
        if (fs[i].first == fs[idx_a.back()].first) continue;

        const auto it =
            partition_point(cbegin(idx_a), cend(idx_a), [&](const auto j) {
                return fs[j].first == fs[i].first;
            });

        if (it == cend(idx_a)) continue;

        if (fs[*it].second == fs[idx_b.back()].second) continue;
        const auto jt =
            partition_point(cbegin(idx_b), cend(idx_b), [&](const auto j) {
                return fs[j].second == fs[j].second;
            });
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> fs(n);

        for (auto &[a, b] : fs) {
            int h, w;
            cin >> h >> w;

            a = max(h, w);
            b = min(h, w);
        }

        cout << in_fronts(move(fs)) << '\n';
    }

    return 0;
}
