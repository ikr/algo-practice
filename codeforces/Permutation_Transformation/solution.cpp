#include <bits/stdc++.h>
using namespace std;
using Iter = vector<int>::const_iterator;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> gather_depths(const vector<int> &xs) {
    const int n = xs.size();
    vector<int> ans(n, -1);

    function<void(int, Iter, Iter)> scan;
    scan = [&](const int level, const Iter first, const Iter last) {
        const auto hi_it = max_element(first, last);
        const auto i = distance(cbegin(xs), hi_it);
        ans[i] = level;

        if (hi_it != first) scan(level + 1, first, hi_it);
        if (hi_it != prev(last)) scan(level + 1, next(hi_it), last);
    };

    scan(0, cbegin(xs), cend(xs));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        cout << gather_depths(xs) << '\n';
    }

    return 0;
}
