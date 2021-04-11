#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> edges(const vector<string> &grid) {
    const int n = sz(grid);
    vector<pii> ans;

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            if (grid[ro][co] == '*') {
                ans.emplace_back(ro, co);
            }
        }
    }

    return ans;
}

vector<pii> sisters(vector<pii> es) {
    assert(sz(es) == 2);
    const int n = sz(es);
    sort(begin(es), end(es));
    const auto [ro1, co1] = es[0];
    const auto [ro2, co2] = es[1];

    if (ro1 == ro2) {
        assert(co1 != co2);
        return {{(ro1 + 1) % n, co1}, {(ro1 + 1) % n, co2}};
    }

    if (co1 == co2) {
        assert(ro1 != ro2);
        return {{ro1, (co1 + 1) % n}, {ro2, (co1 + 1) % n}};
    }

    assert(ro1 != ro2);
    assert(co1 != co2);

    vector<pii> ans;
    for (const int ro : {ro1, ro2}) {
        for (const int co : {co1, co2}) {
            ans.emplace_back(ro, co);
        }
    }
    return ans;
}

void complete_rect(vector<string> &grid) {
    for (const auto [ro, co] : sisters(edges(grid))) {
        grid[ro][co] = '*';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<string> grid(n);
        for (auto &row : grid) cin >> row;

        complete_rect(grid);
        for (const auto &row : grid) cout << row << '\n';
    }

    return 0;
}
