#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
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

        pii xy{0, 0};
        bool yes = false;

        for (const auto x : xs) {
            switch (x) {
            case 'U':
                xy = xy + pii{0, 1};
                break;
            case 'R':
                xy = xy + pii{1, 0};
                break;
            case 'D':
                xy = xy + pii{0, -1};
                break;
            case 'L':
                xy = xy + pii{-1, 0};
                break;
            }

            if (xy == pii{1, 1}) {
                yes = true;
            }
        }

        cout << (yes ? "YES" : "NO") << '\n';
    }

    return 0;
}
