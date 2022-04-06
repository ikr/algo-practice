#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<int> &xs) {
    const auto N = sz(xs);
    const auto ev = inof(count_if(cbegin(xs), cend(xs),
                                  [](const int x) { return (x % 2) == 0; }));
    if (ev == 0 || ev == N) return 0;
    const auto od = N - ev;

    if (od % 2) return ev;
    return min(od / 2, ev);
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

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
