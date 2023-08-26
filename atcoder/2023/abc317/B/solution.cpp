#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;
    ranges::sort(xs);

    const auto ans = [&]() -> int {
        for (int i = 1; i < N; ++i) {
            if (xs[i - 1] + 1 != xs[i]) return xs[i - 1] + 1;
        }

        if (xs[1] == 1) return xs.back() + 1;
        if (xs.back() == 1000) return xs[0] - 1;
        return 0;
    }();

    cout << ans << '\n';
    return 0;
}
