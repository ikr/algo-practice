#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_distinct(const vector<int> &xs) {
    const auto s = accumulate(cbegin(xs), cend(xs), 0);
    int n = 1;
    while ((n + 1) * (n + 2) <= 2 * s) ++n;
    return n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        cout << max_distinct(xs) << '\n';
    }

    return 0;
}
