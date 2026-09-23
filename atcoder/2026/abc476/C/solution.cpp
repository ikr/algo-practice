#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) {
        cin >> x;
    }

    vector<int> tri{xs[0], xs[1], xs[2]};
    cout << *ranges::min_element(tri) << '\n';

    for (int i = 3; i < sz(xs); ++i) {
        tri.push_back(xs[i]);
        sort(rbegin(tri), rend(tri));
        tri.pop_back();

        cout << tri[2] << '\n';
    }

    return 0;
}
