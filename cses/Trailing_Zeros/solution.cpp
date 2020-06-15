#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

int fac_fives(int n) {
    int ans = 0;
    while (n && n % 5 == 0) {
        ++ans;
        n /= 5;
    }
    return ans;
}

int zeros(const int n) {
    if (n <= 20) return n / 5;
    return fac_fives(n) + zeros(n - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << zeros(n) << '\n';

    return 0;
}
