#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> optimal(vector<int> xs) {
    if (sz(xs) == 1) return xs;
    if (sz(xs) == 2) {
        reverse(begin(xs), end(xs));
        return xs;
    }

    const auto n = sz(xs);
    const auto it_hi = max_element(begin(xs) + 1, end(xs));
    const auto hi = inof(distance(begin(xs), it_hi));

    if (hi == n - 1 && xs[n - 2] < xs[0]) {
        rotate(begin(xs), it_hi, end(xs));
        return xs;
    }

    int i = hi - 1;

    return xs;
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

        cout << optimal(move(xs)) << '\n';
    }

    return 0;
}
