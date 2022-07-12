#include <bits/stdc++.h>
#include <cctype>
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

        transform(cbegin(s), cend(s), begin(s), ::tolower);
        const auto yes = s == "yes";
        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
