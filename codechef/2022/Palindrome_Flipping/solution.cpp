#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string reversed(string xs) {
    reverse(begin(xs), end(xs));
    return xs;
}

bool is_possible(const string &xs) {
    const auto n = sz(xs);
    if (n % 2) return true;

    const auto os = count(cbegin(xs), cend(xs), '1');
    const auto zs = n - os;
    return (os % 2 == 0) && (zs % 2 == 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
