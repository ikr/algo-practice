#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string proto{"Timur"};
    sort(begin(proto), end(proto));

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        sort(begin(xs), end(xs));
        const auto yes = xs == proto;
        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
