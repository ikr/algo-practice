#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> solve(vector<int> xs, const vector<int> &ys) {
    sort(rbegin(xs), rend(xs));

    vector<int> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    vector<int> result(sz(ys), -1);
    for (int i = 0; i < sz(ys); ++i) {
        const auto it = lower_bound(cbegin(ss), cend(ss), ys[i]);
        if (it != cend(ss)) {
            result[i] = inof(distance(cbegin(ss), it)) + 1;
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        vector<int> ys(q);
        for (auto &y : ys) cin >> y;

        for (const auto r : solve(move(xs), ys)) {
            cout << r << '\n';
        }
    }

    return 0;
}
