#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_sum(const vector<ll> &xs) {
    priority_queue<ll, vector<ll>, greater<ll>> pq(cbegin(xs), cend(xs));

    for (;;) {
        const auto a = pq.top();
        pq.pop();
        const auto b = pq.top();
        pq.pop();

        if (a + b < -a - b) {
            pq.push(-a);
            pq.push(-b);
        } else {
            pq.push(a);
            pq.push(b);
            break;
        }
    }

    ll ans{};
    while (!pq.empty()) {
        ans += pq.top();
        pq.pop();
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

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_sum(xs) << '\n';
    }

    return 0;
}
