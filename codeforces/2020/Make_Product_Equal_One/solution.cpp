#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int n;
    cin >> n;

    unsigned long long ans = 0;
    int num_zeros = 0;
    int num_negs = 0;

    for (unsigned int i = 0; i != n; ++i) {
        int x;
        cin >> x;

        if (x > 0) {
            ans += (x - 1);
            x = 1;
        } else if (x < 0) {
            ans += abs(x + 1);
            x = -1;
            ++num_negs;
        } else {
            ++num_zeros;
        }
    }

    if (num_negs % 2) {
        if (num_zeros) {
            ++ans;
            --num_zeros;
        } else {
            ans += 2;
        }
    }

    ans += num_zeros;

    cout << ans << '\n';
}
