#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll, vector<ll>> gather_stamp_and_spans(const ll n, const vector<ll> &xs) {
    ll stamp = 1e18;
    vector<ll> spans;
    spans.reserve(xs.size());

    ll pre = 0;

    for (const auto x : xs) {
        if (x == pre + 1) {
            pre = x;
            continue;
        }

        const ll d = x - pre - 1;
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

ll solve(const ll n, const vector<ll> &xs) {
    const auto [k, spans] = gather_stamp_and_spans(n, xs);

    ll ans = 0;

    for (const ll y : spans) {
        ans += (y / k);
        if (y % k) ++ans;
    }

    return ans;
}

ll oracle_solve(const ll n, vector<ll> a) {
    vector<int> b;
    a.push_back(0);
    a.push_back(n + 1);
    sort(a.begin(), a.end());

    int tmp;
    for (auto i = 0U; i < a.size() - 1; i++) {
        tmp = a[i + 1] - a[i] - 1;
        if (tmp != 0) {
            b.push_back(tmp);
        }
    }

    sort(b.begin(), b.end());

    int k, sum = 0;
    if (b.size() == 0)
        return 0;
    else {
        k = b[0];

        for (auto i = 0U; i < b.size(); i++) {
            if (b[i] % k == 0)
                sum += (double)b[i] / (double)k;
            else
                sum += (double)b[i] / (double)k + 1;
        }
        return sum;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;

    if (!m) {
        cout << n << '\n';
        cout << n << '\n';
        return 0;
    }

    vector<ll> xs(m, 0);
    for (auto &x : xs) {
        cin >> x;
    }

    sort(begin(xs), end(xs));
    cout << solve(n, xs) << '\n';
    cout << oracle_solve(n, xs) << '\n';
    return 0;
}
