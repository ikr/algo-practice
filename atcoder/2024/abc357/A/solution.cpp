#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    vector<int> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto result = [&]() -> int {
        if (xs[0] > m) return 0;
        if (ss.back() <= m) return n;
        const auto it = lower_bound(cbegin(ss), cend(ss), m);
        return inof(lower_bound(cbegin(ss), cend(ss), m) - cbegin(ss)) +
               (*it == m ? 1 : 0);
    }();
    cout << result << '\n';
    return 0;
}
