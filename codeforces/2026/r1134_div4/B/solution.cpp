#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char flip(const char x) { return x == 'B' ? 'R' : 'B'; }

int flips_num(const string &xs, char cur) {
    int result{};

    for (const char x : xs) {
        if (x == cur) {
            cur = flip(cur);
        } else {
            ++result;
        }
    }

    return result;
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
        assert(sz(xs) == n);

        const int result = flips_num(xs, 'R');
        cout << result << '\n';
    }

    return 0;
}
