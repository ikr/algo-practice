#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

string solve(string xs, const int d) {
    const auto it = find_if(cbegin(xs), cend(xs), [d](const char x) {
        return (inof(x) - inof('0')) < d;
    });
    xs.insert(it, chof(inof('0') + d));
    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << solve(move(xs), d) << '\n';
    }

    return 0;
}
