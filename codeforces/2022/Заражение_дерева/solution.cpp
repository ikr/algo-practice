#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> children(const vector<int> &P) {
    vector<vector<int>> result(sz(P));
    for (int u = 0; u < sz(P); ++u) {
        if (P[u] >= 0) result[P[u]].push_back(u);
    }
    return result;
}

int min_time(const int inject_only, const vector<int> &sibs) {
    const auto total_inj_time = sz(sibs);

    int extra_burn_down_time{};
    for (const auto x : sibs) {
        if (x - 1 > total_inj_time) {
            extra_burn_down_time =
                max(extra_burn_down_time, x - 1 - total_inj_time);
        }
    }

    return total_inj_time + max(inject_only, extra_burn_down_time);
}

int min_time(const vector<int> &P) {
    const auto ch = children(P);
    vector<bool> inject_only(sz(P), true);
    vector<int> sibs;

    for (const auto &vs : ch) {
        if (sz(vs) > 1) {
            for (const auto v : vs) inject_only[v] = false;
            sibs.push_back(sz(vs));
        }
    }

    sort(rbegin(sibs), rend(sibs));

    return min_time(inof(count(cbegin(inject_only), cend(inject_only), true)),
                    sibs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> P(n, -1);
        for (int i = 1; i < n; ++i) {
            cin >> P[i];
            --P[i];
        }

        cout << min_time(P) << '\n';
    }

    return 0;
}
