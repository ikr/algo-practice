#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int A0, B0;
        cin >> A0 >> B0;

        const auto yes = (abs(A0 - B0) % 2) == 0;
        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
