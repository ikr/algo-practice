#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
static const ll M = 1e9 + 7;
template <typename T> constexpr int intof(const T x) { return static_cast<int>(x); }

int count_equlibrium_splits(const int n) {
    const int total = n * (n + 1) / 2;
    if (total % 2) return 0;
    const int target_sum = total / 2;
    
    // number of subsets [using numbers up to i] [having sum of exactly j]
    vvi ssnum(n + 1, vi(target_sum + 1, 0));
    ssnum[0][0] = 1;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target_sum; ++j) {
            ll curr = ssnum[i - 1][j];
            if (j - i >= 0) curr += ssnum[i - 1][j - i];
            ssnum[i][j] = intof(curr % M);
        }
    }
    
    return ssnum.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << count_equlibrium_splits(n) << '\n';
    
    return 0;
}
