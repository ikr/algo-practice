#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    set<int> xs;

    int t = 5;
    while (t--) {
        int x;
        cin >> x;
        xs.insert(x);
    }

    cout << sz(xs) << '\n';
    return 0;
}
