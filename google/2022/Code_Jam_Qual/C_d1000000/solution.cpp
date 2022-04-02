#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int solve(const vector<int> &xs) {
    int need = 1;

    for (const auto x : xs) {
        if (x >= need) ++need;
    }

    return need - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
