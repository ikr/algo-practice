#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> count_platforms_to_build(const string &bits, const int k) {
    const auto has_platform = [&bits](const int i) { return bits[i] == '1'; };
    const int n = bits.size();
    vector<int> ans(n, 0);

    for (int i = n - 1; i >= 0; --i) {
        if (i + k >= n) {
            ans[i] = has_platform(i) ? 0 : 1;
        } else {
            ans[i] = ans[i + k] + (has_platform(i) ? 0 : 1);
        }
    }

    return ans;
}

ll min_level_modification_cost(const string &bits, const int p, const int k,
                               const ll cbuild, const ll cdrop) {
    const int n = bits.size();
    const auto to_build = count_platforms_to_build(bits, k);

    ll ans = 1e18;

    for (int i = 0; i + p - 1 <= n - 1; ++i) {
        ans = min(ans, i * cdrop + to_build[i + p - 1] * cbuild);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, p, k;
        cin >> n >> p >> k;

        string bits(n, ' ');
        cin >> bits;

        int cbuild, cdrop;
        cin >> cbuild >> cdrop;

        cout << min_level_modification_cost(bits, p, k, cbuild, cdrop) << '\n';
    }

    return 0;
}
