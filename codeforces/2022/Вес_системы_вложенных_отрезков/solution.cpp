#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void solve(const int n, const vector<pii> &xws) {
    priority_queue<pii> pq;

    for (auto i = 0; i < sz(xws); ++i) {
        const auto [x, w] = xws[i];
        pq.emplace(-w, i);
    }

    deque<int> idx;

    while (sz(idx) < 2 * n) {
        const auto [_, i] = pq.top();
        pq.pop();
        idx.push_back(i);
    }

    int w{};
    for (const auto i : idx) {
        w += xws[i].second;
    }

    sort(begin(idx), end(idx),
         [&](const int i, const int j) { return xws[i].first < xws[j].first; });

    cout << w << '\n';

    while (!idx.empty()) {
        const auto i = idx.front();
        idx.pop_front();

        const auto j = idx.back();
        idx.pop_back();

        cout << (i + 1) << ' ' << (j + 1) << '\n';
    }

    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pii> xws(m);
        for (auto &[x, w] : xws) {
            cin >> x >> w;
        }

        solve(n, xws);
    }

    return 0;
}
