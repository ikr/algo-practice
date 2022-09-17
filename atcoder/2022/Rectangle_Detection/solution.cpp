#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A{}, C{};
    int B{}, D{};

    for (int i = 1; i <= 10; ++i) {
        string row;
        cin >> row;

        if (A) {
            if (!B && row.find('#') == row.npos) {
                B = i - 1;
            }
        } else {
            const auto lo = row.find('#');
            if (lo == row.npos) continue;
            A = i;

            const auto hi = row.rfind('#');
            C = inof(lo) + 1;
            D = inof(hi) + 1;
        }
    }

    if (!B) B = 10;

    cout << A << ' ' << B << '\n';
    cout << C << ' ' << D << '\n';
    return 0;
}
