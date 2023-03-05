#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> index_components(const int n, const int k) {
    const auto in_bounds = [&](const int i) { return 0 <= i && i < n; };

    atcoder::dsu uf(n);
    for (int i = 0; i < n; ++i) {
        for (const auto d : {k, -k, k + 1, -(k + 1)}) {
            if (in_bounds(i + d)) uf.merge(i, i + d);
        }
    }

    return uf.groups();
}

string projection(const string &xs, const vector<int> &ii) {
    string ans(sz(ii), ' ');
    for (int j = 0; j < sz(ii); ++j) ans[j] = xs[ii[j]];
    return ans;
}

bool are_equal_sorted(string s, string t) {
    sort(begin(s), end(s));
    sort(begin(t), end(t));
    return s == t;
}

bool is_possible(const string &s, const string &t, const int k) {
    auto cs = index_components(sz(s), k);
    for (auto &ii : cs) {
        if (!are_equal_sorted(projection(s, ii), projection(t, ii))) {
            return false;
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;

        string s, t;
        cin >> s >> t;

        assert(sz(s) == n);
        assert(sz(t) == n);

        cout << (is_possible(s, t, k) ? "YES" : "NO") << '\n';
    }

    return 0;
}
