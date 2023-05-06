#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<int, int>> run_length_encode(const vector<int> &xs) {
    vector<pair<int, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

int max_blank_space(const vector<int> &xs) {
    const auto rle = run_length_encode(xs);
    int ans{};
    for (const auto &[v, f] : rle) {
        if (v == 0) {
            ans = max(ans, f);
        }
    }
    return ans;
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

        cout << max_blank_space(xs) << '\n';
    }

    return 0;
}
