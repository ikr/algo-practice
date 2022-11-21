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

vector<int> advantages(const vector<int> &xs) {
    multiset<int> xss(cbegin(xs), cend(xs));
    vector<int> result(sz(xs));

    for (int i = 0; i < sz(xs); ++i) {
        xss.erase(xss.find(xs[i]));
        result[i] = xs[i] - *crbegin(xss);
        xss.insert(xs[i]);
    }

    return result;
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

        cout << advantages(xs) << '\n';
    }

    return 0;
}
