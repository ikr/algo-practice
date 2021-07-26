#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<int, vector<int>> gather_stamp_and_spans(const int n,
                                              const vector<int> &xs) {
    int stamp = INT_MAX;
    vector<int> spans;
    spans.reserve(xs.size());

    int pre = 0;

    for (const auto x : xs) {
        if (x == pre + 1) {
            pre = x;
            continue;
        }

        const int d = x - pre - 1;
        stamp = min(stamp, d);
        spans.push_back(d);
        pre = x;
    }

    if (pre != n) {
        stamp = min(stamp, n - pre);
        spans.push_back(n - pre);
    }

    return {stamp, spans};
}

ll solve(const int n, const vector<int> &xs) {
    const auto [k, spans] = gather_stamp_and_spans(n, xs);

    ll ans = 0;

    for (const int y : spans) {
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
        cout << 1 << '\n';
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
