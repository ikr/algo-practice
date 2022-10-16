#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &xs, const string &ys) {
    vector<vector<int>> occ_x;
    {
        map<int, int> idx_x;
        for (int i = 0; i < sz(xs); ++i) {
            if (idx_x.contains(xs[i])) {
                occ_x[idx_x.at(xs[i])].push_back(i);
            } else {
                occ_x.push_back(vector<int>{i});
                idx_x[xs[i]] = sz(occ_x) - 1;
            }
        }
    }

    vector<vector<int>> occ_y;
    {
        map<char, int> idx_y;
        for (int i = 0; i < sz(ys); ++i) {
            if (idx_y.contains(ys[i])) {
                occ_y[idx_y.at(ys[i])].push_back(i);
            } else {
                occ_y.push_back(vector<int>{i});
                idx_y[ys[i]] = sz(occ_y) - 1;
            }
        }
    }

    return occ_x == occ_y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        string ys;
        cin >> ys;
        assert(sz(ys) == n);

        cout << (is_possible(xs, ys) ? "YES" : "NO") << '\n';
    }

    return 0;
}
