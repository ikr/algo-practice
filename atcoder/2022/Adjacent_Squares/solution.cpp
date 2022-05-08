#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W, R, C;
    cin >> H >> W >> R >> C;

    int ans = 4;
    if (R == 1) --ans;
    if (C == 1) --ans;
    if (R == H) --ans;
    if (C == W) --ans;
    cout << ans << '\n';

    return 0;
}
