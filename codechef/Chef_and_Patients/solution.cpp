#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> wait_times(const vector<int> &xs) {
    const int n = xs.size();

    vector<pair<int, int>> ys(n);
    for (int i = 1; i <= n; ++i) {
        ys[i - 1] = pair{-xs[i - 1], i};
    }

    sort(begin(ys), end(ys));

    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[ys[i].second - 1] = i + 1;
    }
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

        cout << wait_times(xs) << '\n';
    }

    return 0;
}
