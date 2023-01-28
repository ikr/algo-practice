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

    int f{}, a{};
    while (t--) {
        string s;
        cin >> s;

        f += s == "For";
        a += s == "Against";
    }

    const auto yes = f > a;
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
