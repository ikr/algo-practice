#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using usi = unordered_set<int>;

usi combine(const usi &xs, const int y) {
    usi ans = xs;
    ans.insert(y);
    for (const int x : xs) ans.insert(x + y);    
    return ans;
}

vi count_sums(const vi &xs) {
    const int sz = xs.size();
    vector<usi> dp(sz, usi{});
    dp[0] = usi{xs[0]};
    for (int i = 1; i < sz; ++i) dp[i] = combine(dp[i - 1], xs[i]);
    
    vi ans(dp.back().cbegin(), dp.back().cend());
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;

    const vi ans = count_sums(xs);
    cout << ans.size() << '\n';
    for (const int y : ans) cout << y << ' ';
    cout << '\n';
    return 0;
}
