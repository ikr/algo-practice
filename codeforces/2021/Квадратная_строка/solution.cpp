#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_square(const string &xs) {
    if (sz(xs) % 2) return false;
    const int d = sz(xs) / 2;
    return xs.substr(0, d) == xs.substr(d);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << (is_square(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
