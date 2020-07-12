#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int solve(const vi &xs) {
    const int sz = xs.size();

    int ans = 0;
    int max_so_far = -1;

    for (int i = 0; i < sz; ++i) {
        const int x = xs[i];
        if (x > max_so_far) {
            if (i == sz - 1 || x > xs[i + 1]) ++ans;
            max_so_far = x;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int sz;
        cin >> sz;
        vi xs(sz, 0);
        for (auto &x : xs) cin >> x;
        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
