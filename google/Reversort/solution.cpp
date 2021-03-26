#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int solve(vi xs) {
    int ans = 0;
    assert(!xs.empty());

    for (auto it = begin(xs); it != prev(end(xs)); ++it) {
        const auto jt = min_element(it, end(xs));

        ans += inof(distance(it, jt)) + 1;
        reverse(it, next(jt));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
