#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll top_skill(vector<int> xs, vector<int> ys) {
    if (sz(xs) + sz(ys) < 11 || sz(xs) < 4 || sz(ys) < 4) {
        return -1;
    }

    vector<ll> team;
    for (int i = 0; i < 4; ++i) {
        team.push_back(xs.back());
        xs.pop_back();
        team.push_back(ys.back());
        ys.pop_back();
    }

    xs.insert(cend(xs), cbegin(ys), cend(ys));
    sort(begin(xs), end(xs));

    for (int i = 0; i < 3; ++i) {
        team.push_back(xs.back());
        xs.pop_back();
    }

    return accumulate(cbegin(team), cend(team), 0LL);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        vector<int> ys(m);
        for (auto &y : ys) cin >> y;
        sort(begin(ys), end(ys));

        cout << top_skill(std::move(xs), std::move(ys)) << '\n';
    }

    return 0;
}
