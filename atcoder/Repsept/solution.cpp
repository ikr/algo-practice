#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ten_exp_mod(const int power, const int m) {
    if (!power) return 1;
    if (power % 2) return (10 * ten_exp_mod(power - 1, m)) % m;

    const ll sq = ten_exp_mod(power / 2, m);
    return (sq * sq) % m;
}

int solve(const int K) {
    for (int i = 1; i < K; ++i) {
        if (ten_exp_mod(i, K) == 1) return i;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int K;
    cin >> K;
    cout << solve(K) << '\n';

    return 0;
}
