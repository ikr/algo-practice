#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    set<int> toop;
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        if (toop.contains(x)) {
            toop.erase(x);
        } else {
            toop.insert(x);
        }
    }

    cout << (n - sz(toop)) << '\n';
    return 0;
}
