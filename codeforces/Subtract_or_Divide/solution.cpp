#include <bits/stdc++.h>
using namespace std;

int next_x(const int x) {
    assert(x != 1);
    const int lim = sqrt(x);
    int q = -1;
    for (int i = lim; i > 1; --i) {
        if (x % i) continue;
        const int j = x / i;
        q = max({q, i, j});
    }
    return (q == -1) ? (x - 1) : (x / q);
}

int moves(const int n) {
    int x = n;
    int ans = 0;

    while (x != 1) {
        x = next_x(x);
        ++ans;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t{0};
    cin >> t;
    while (t--) {
        int n{0};
        cin >> n;
        cout << moves(n) << '\n';
    }

    return 0;
}
