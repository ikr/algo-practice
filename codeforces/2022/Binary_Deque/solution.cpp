#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<int> &xs, const int s) {
    const auto total = accumulate(cbegin(xs), cend(xs), 0);
    if (total < s) return -1;
    if (total == s) return 0;

    vector<int> suf(sz(xs));
    partial_sum(crbegin(xs), crend(xs), begin(suf));

    vector<int> pre(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(pre));

    // cerr << "pre:" << pre << " suf:" << suf << endl;

    const auto target = total - s;
    int result = inof(distance(cbegin(pre),
                               lower_bound(cbegin(pre), cend(pre), target))) +
                 1;

    // cerr << "result0:" << result << " target:" << target << endl;

    for (int i = 0; i < sz(suf); ++i) {
        const auto d = i + 1;
        const auto tail = suf[i];

        // cerr << "d:" << d << " tail:" << tail << endl;

        if (tail == target) {
            result = min(result, d);
            // cerr << "a) set result:" << result << endl;
            break;
        }

        const auto it = lower_bound(cbegin(pre), cend(pre), target - tail);
        const auto dd = inof(distance(cbegin(pre), it)) + 1;

        // cerr << "dd:" << dd << endl;
        result = min(result, d + dd);
        // cerr << "b) set result:" << result << endl;
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
