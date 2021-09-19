#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Tri = tuple<int, int, int>;

ll solve(const vector<Tri> &atts, const int K) {
    map<int, vi> by_s;
    map<int, vi> by_e;

    set<int> ms;

    for (const auto [h, s, e] : atts) {
        by_s[s].push_back(h);
        by_e[e + 1].push_back(h);
        ms.insert(s);
        ms.insert(e + 1);
    }

    ll ans = 0;
    ll curr = 0;
    multiset<int> hp;
    multiset<int> rs;

    for (const auto x : ms) {
        for (const auto h : by_s[x]) {
            if (!rs.empty() && *prev(cend(rs)) > h) {
                const auto it = prev(cend(rs));
                hp.insert(*it);
                curr += *it;
                rs.erase(it);

                rs.insert(h);
            } else {
                hp.insert(h);
                curr += h;
            }
        }

        for (const auto h : by_e[x]) {
            const auto it = hp.find(h);

            if (it != cend(hp)) {
                hp.erase(it);
                curr -= h;
            } else {
                const auto jt = rs.find(h);
                assert(jt != cend(rs));
                rs.erase(jt);
            }
        }

        while (sz(hp) > K) {
            const auto h = *cbegin(hp);
            curr -= h;
            hp.erase(cbegin(hp));
            rs.insert(h);
        }

        while (sz(hp) < K && !rs.empty()) {
            const auto it = prev(cend(rs));
            hp.insert(*it);
            curr += *it;
            rs.erase(it);
        }

        ans = max(ans, curr);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int D, N, K;
        cin >> D >> N >> K;

        vector<Tri> atts(N);
        for (auto &[h, s, e] : atts) {
            cin >> h >> s >> e;
            --s;
            --e;
        }

        cout << "Case #" << i << ": " << solve(atts, K) << '\n';
    }

    return 0;
}
