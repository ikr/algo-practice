#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, s;
    cin >> n >> s;
    --s;

    ll l;
    cin >> l;

    vector<ll> aa(n - 1, 0LL);
    for (auto &a : aa) {
        cin >> a;
    }

    vector<ll> dist(n, LLONG_MAX);
    dist[s] = 0LL;

    for (int i = s - 1; i >= 0; --i) {
        dist[i] = dist[i + 1] + aa[i];
    }

    for (int i = s + 1; i <= n - 1; ++i) {
        dist[i] = dist[i - 1] + aa[i - 1];
    }

    int result = 0;

    for (int i = s; i >= 0; --i) {
        for (int j = s; j <= n - 1; ++j) {
            if (dist[i] * 2 + dist[j] <= l || 2 * dist[j] + dist[i] <= l) {
                result = max(result, s - i + j - s + 1);
            }
        }
    }

    cout << result << '\n';
    return 0;
}
