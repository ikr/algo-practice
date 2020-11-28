#include <bits/stdc++.h>
using namespace std;

int max_gcd_of_pair(const vector<int> &xs) {
    const int hi = *max_element(cbegin(xs), cend(xs));

    vector<int> freqs_by_divisor(hi + 1, 0);
    freqs_by_divisor[1] = xs.size();

    for (const int x : xs) {
        ++freqs_by_divisor[x];

        const int lim = sqrt(x);
        for (int i = 2; i <= lim; ++i) {
            if (x % i) continue;
            ++freqs_by_divisor[i];
            if (x / i > lim) ++freqs_by_divisor[x / i];
        }
    }

    for (int i = hi; i >= 0; --i) {
        if (freqs_by_divisor[i] >= 2) return i;
    }

    assert(false && "/o\\");
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << max_gcd_of_pair(xs) << '\n';
    return 0;
}
