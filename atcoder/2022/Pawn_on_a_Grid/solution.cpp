#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    int result{};
    for (int i = 0; i < H; ++i) {
        string row;
        cin >> row;
        result += count(cbegin(row), cend(row), '#');
    }

    cout << result << '\n';
    return 0;
}
