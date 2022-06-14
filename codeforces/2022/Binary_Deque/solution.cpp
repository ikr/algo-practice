#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

deque<pii> runlength_encode(const vector<int> &xs) {
    deque<pii> result{{xs[0], 1}};

    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == result.back().first) {
            ++(result.back().second);
        } else {
            result.emplace_back(xs[i], 1);
        }
    }

    return result;
}

int min_ops(const vector<int> &xs, const int s) {
    const auto total = accumulate(cbegin(xs), cend(xs), 0);
    if (total < s) return -1;

    auto q = runlength_encode(xs);

    int result{};
    auto cur = total;
    while (cur > s) {
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;

        vector xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << min_ops(xs, s) << '\n';
    }

    return 0;
}
