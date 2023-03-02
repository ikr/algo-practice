#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_force(const vector<int> &xs) {
    ll ans{};
    priority_queue<int> q;

    for (const auto x : xs) {
        if (x == 0) {
            if (!q.empty()) {
                ans += q.top();
                q.pop();
            }
        } else {
            q.push(x);
        }
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

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_force(xs) << '\n';
    }

    return 0;
}
