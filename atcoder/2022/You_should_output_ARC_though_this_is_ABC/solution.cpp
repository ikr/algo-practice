#include <array>
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int R, C;
    cin >> R >> C;
    --R;
    --C;

    array<array<int, 2>, 2> grid{};
    for (auto &row : grid) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    cout << grid[R][C] << '\n';
    return 0;
}
