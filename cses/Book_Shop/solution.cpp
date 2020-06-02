#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int max_pages(const int max_price, const vi &prices, const vi &pages) {
    const int sz = prices.size();
    assert(sz == pages.size());
    if (sz == 0) return 0;
    
    // max pages [using i first books] [having total price of exactly j]
    vvi dp(sz + 1, vi(max_price + 1, 0));
    
    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= max_price; ++j) {
            const int price = prices[i - 1];
            dp[i][j] = dp[i - 1][j];
            
            if (j - price >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - price] + pages[i - 1]);
            }
        }
    }

    return *max_element(dp.back().cbegin(), dp.back().cend());
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz, max_price;
    cin >> sz >> max_price;
    
    vi prices(sz, 0);
    for (auto &x : prices) cin >> x;
    
    vi pages(sz, 0);
    for (auto &x : pages) cin >> x;

    cout << max_pages(max_price, prices, pages) << '\n';
    return 0;
}
