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
        string s;
        cin >> s;

        const string xs{"codeforces"};
        const auto x = s[0];
        const auto yes = find(cbegin(xs), cend(xs), x) != cend(xs);

        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
