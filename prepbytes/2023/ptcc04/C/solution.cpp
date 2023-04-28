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

int min_pyramids_num(const vector<int> &xs) {
    multiset<int> ans;
    for (const auto x : xs) {
        const auto it = ans.upper_bound(x);
        if (it != xend(ans)) ans.erase(it);
        ans.insert(x);
    }
    return sz(ans);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    cout << min_pyramids_num(xs) << '\n';
    return 0;
}
