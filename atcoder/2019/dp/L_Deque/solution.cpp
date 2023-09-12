#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> constexpr int intof(const T x) {
    return static_cast<int>(x);
}

ll final_difference(const vector<int> &xs) {
    const int n = intof(xs.size());
    vector<vector<ll>> diff(n, vector<ll>(n, 0));

    for (int l = n - 1; l >= 0; --l) {
        for (int r = l; r < n; ++r) {
            if (l == r) {
                diff[l][l] = xs[l];
            } else {
                diff[l][r] =
                    max(xs[l] - diff[l + 1][r], xs[r] - diff[l][r - 1]);
            }
        }
    }

    return diff[0][n - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    cout << final_difference(xs) << '\n';
    return 0;
}
