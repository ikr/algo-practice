#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    int sz;
    cin >> sz;

    vector<ll> acts(sz, 0);
    vector<pair<ll, int>> act_idx_pairs;
    for (int i = 0; i != sz; ++i) {
        ll act;
        cin >> act;

        acts[i] = act;
        act_idx_pairs.emplace_back(act, i);
    }

    sort(act_idx_pairs.begin(), act_idx_pairs.end(), greater<pair<ll, int>>{});
    cout << "pairs " << act_idx_pairs << endl;

    // [filled at left side][filled at right side]
    vector<vector<ll>> dp(sz + 1, vector<ll>(sz + 1, 0));
    
    for (int i = 1; 2 * i - 1 <= sz; ++i) {
        const auto [act, idx] = act_idx_pairs[i - 1];

        cout << "pair #" << (i - 1) << endl;
        cout << "L ACTS, DIFF " << (act + acts[i - 1]) << ", " << abs(idx - i + 1) << endl;
        dp[i][i - 1] = (act + acts[i - 1]) * abs(idx - i + 1) + dp[i - 1][i - 1];
        
        cout << "R ACTS, DIFF " << (act + acts[sz - i]) << ", " << abs(idx - sz + i + 2) << endl;
        dp[i - 1][i] = (act + acts[sz - i]) * abs(idx - sz + i + 2) + dp[i - 1][i - 1];
    }

    cout << dp << endl;

    return 0;
}
