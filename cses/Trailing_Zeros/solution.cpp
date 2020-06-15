#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;

int exp(const int base, const int power) {
    if (!power) return 1;
    if (power % 2) return base * exp(base, power - 1);

    const int sq = exp(base, power / 2);
    return sq * sq;
}

int max_5_exp_up_to(const int n) {
    int ans = 0;
    ll prod = 1;
    while (prod * 5 <= n) {
        ++ans;
        prod *= 5;
    }
    return ans;
}

int zeros(const int n) {
    const int me = max_5_exp_up_to(n);
    vi count_by_power(me + 1, 0);
    for (int i = me; i > 0; --i) {
        int e = exp(5, i);
        count_by_power[i] += (n / e);
    }
    return accumulate(count_by_power.cbegin(), count_by_power.cend(), 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << zeros(n) << '\n';

    return 0;
}
