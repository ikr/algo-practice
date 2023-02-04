#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_teleports(const int c, const vector<int> &xs) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < sz(xs); ++i) {
        pq.push(i + 1 + xs[i]);
    }

    int ans{};
    auto cur = c;
    while (!pq.empty() && pq.top() <= cur) {
        cur -= pq.top();
        pq.pop();
        ++ans;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_teleports(c, xs) << '\n';
    }

    return 0;
}
