#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_inversions(const vi &xs) {
    vi ys = xs;
    sort(begin(ys), end(ys));
    ys.erase(unique(begin(ys), end(ys)), end(ys));

    unordered_map<int, int> idx;
    for (int i = 0; i < sz(ys); ++i) idx[ys[i]] = i;

    int ans = 0;
    vi q;
    q.reserve(sz(xs));

    for (const auto x : xs) {
        const auto ord = idx.at(x);
        const auto it = lower_bound(cbegin(q), cend(q), ord);
        const auto jt = upper_bound(it, cend(q), ord);

        if (q.empty()) {
            q.push_back(ord);
            continue;
        }

        ans += inof(min(distance(cbegin(q), it), distance(jt, cend(q))));
        q.insert(it, ord);
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

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_inversions(xs) << '\n';
    }

    return 0;
}
