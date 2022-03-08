#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> decompose(vector<int> xs) {
    deque<int> dq;

    for (int x = sz(xs); x >= 1; --x) {
        const auto it = find(cbegin(xs), cbegin(xs) + x, x);
        const auto pos = inof(distance(cbegin(xs), it)) + 1;
        if (pos > x) return {};

        dq.push_front(pos == x ? 0 : pos);
        rotate(begin(xs), begin(xs) + pos, begin(xs) + x);
    }

    return vector<int>(cbegin(dq), cend(dq));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        const auto result = decompose(move(xs));
        if (result.empty()) {
            cout << "-1\n";
        } else {
            cout << result << '\n';
        }
    }

    return 0;
}
