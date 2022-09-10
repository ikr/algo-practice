#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s, t;
    cin >> s >> t;

    const bool yes = t.find(s) == 0U;
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
