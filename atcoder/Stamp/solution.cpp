#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int stamp_size(const int n, const vector<int> &xs) {
    int ans = 1e9 + 41;

    int pre = 0;

    for (const auto x : xs) {
        if (x == pre || x - 1 == pre) {
            pre = x;
            continue;
        }

        ans = min(ans, x - pre - 1);
        pre = x;
    }

    if (pre != n) {
        ans = min(ans, n - pre);
    }

    return ans;
}

vector<int> span_lengths(const int n, const vector<int> &xs) {
    vector<int> ans;
    ans.reserve(xs.size());

    int pre = 0;

    for (const auto x : xs) {
        if (x == pre || x - 1 == pre) {
            pre = x;
            continue;
        }

        ans.push_back(x - pre - 1);
        pre = x;
    }

    if (pre != n) {
        ans.push_back(n - pre);
    }

    return ans;
}

ll solve(const int n, const vector<int> &xs) {
    const int k = stamp_size(n, xs);

    ll ans = 0;

    for (const int y : span_lengths(n, xs)) {
        ans += (y / k);
        if (y % k) ++ans;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    if (!m) {
        cout << n << '\n';
        return 0;
    }

    vector<int> xs(m, 0);
    for (auto &x : xs) {
        cin >> x;
    }

    sort(begin(xs), end(xs));
    cout << solve(n, xs) << '\n';
    return 0;
}
