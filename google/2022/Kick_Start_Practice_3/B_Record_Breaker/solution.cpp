#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

int record_breaking_days(const vector<int> &xs) {
    int hi = INT_MIN;
    int result{};

    for (int i = 0; i < sz(xs); ++i) {
        const int right = i == sz(xs) - 1 ? INT_MIN : xs[i + 1];
        result += (hi < xs[i] && xs[i] > right);
        hi = max(hi, xs[i]);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << record_breaking_days(xs) << '\n';
    }

    return 0;
}
