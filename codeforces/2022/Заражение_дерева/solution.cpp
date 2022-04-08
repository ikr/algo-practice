#include <iostream>
#include <map>
#include <set>
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

int min_time(const vector<int> &P) {
    const auto ch = children(P);
    set<int> just_inject;
    for (int u = 0; u < sz(P); ++u) just_inject.insert(u);

    int hi_chain{};
    map<int, int> ch_f;
    int num_chains{};

    for (const auto &vs : ch) {
        if (sz(vs) > 1) {
            for (const auto v : vs) just_inject.erase(v);
            hi_chain = max(hi_chain, sz(vs));
            ++ch_f[sz(vs)];
            ++num_chains;
        }
    }

    const auto req_injects = num_chains + sz(just_inject);
    return max(req_injects, (ch_f[hi_chain] / 2) * (hi_chain - 1));
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
