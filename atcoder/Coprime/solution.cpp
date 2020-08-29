#include <bits/stdc++.h>
using namespace std;

vector<bool> primes(const int lim) {
    vector<bool> ans(lim + 1, true);
    ans[0] = false;
    ans[1] = false;

    int curr = 2;
    ans[2] = true;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    return 0;
}
