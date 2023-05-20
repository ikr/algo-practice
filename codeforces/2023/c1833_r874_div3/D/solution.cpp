#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (auto i = xss.cbegin(); i != xss.cend(); ++i) {
        if (i != xss.cbegin()) os << " | ";
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
    const auto it_hi = max_element(cbegin(xs) + 1, cend(xs));
    const auto hi = inof(distance(cbegin(xs), it_hi));

    vector<vector<int>> alt;

    if (hi == n - 1) {
        int i = hi;
        while (i > 0 && xs[i - 1] > xs[0]) --i;

        vector<int> ys;
        ys.reserve(sz(xs));
        for (int j = hi; j >= i; --j) ys.push_back(xs[j]);
        ys.insert(cend(ys), cbegin(xs), cbegin(xs) + i);

        alt.emplace_back(move(ys));
    }

    {
        const int j = hi - 1;
        int i = j;
        while (i > 0 && xs[i - 1] > xs[0]) --i;

        vector<int> ys(cbegin(xs) + hi, cend(xs));
        ys.reserve(sz(xs));

        for (int k = j; k >= i; --k) ys.push_back(xs[k]);
        ys.insert(cend(ys), cbegin(xs), cbegin(xs) + i);
        alt.emplace_back(move(ys));
    }

    sort(begin(alt), end(alt));
    // cerr << "alt: " << alt << endl;
    return alt.back();
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
