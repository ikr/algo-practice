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

bool are_equal_at(const string &s, const string &t, const vector<int> &ii) {
    return all_of(cbegin(ii), cend(ii),
                  [&](const int i) { return s[i] == t[i]; });
}

void sort_indices(const string &xs, vector<int> &ii) {
    stable_sort(begin(ii), end(ii), [&](const int i, const int j) {
        return inof(xs[i]) < inof(xs[j]);
    });
}

bool is_possible(const string &s, const string &t, const int k) {
    auto cs = index_components(sz(s), k);
    for (auto &ii : cs) {
        auto jj = ii;
        sort_indices(s, ii);
        sort_indices(t, jj);

        if (ii != jj) return false;
        if (!are_equal_at(s, t, ii)) return false;
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
