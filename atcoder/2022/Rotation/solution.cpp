#include <cassert>
#include <iostream>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    for (int i = 1, p = 0; i <= Q; ++i) {
        int cmd, k;
        cin >> cmd >> k;

        if (cmd == 1) {
            p += k;
            p %= N;
        } else {
            assert(cmd == 2);
            --k;

            const auto j = [&]() -> int {
                if (k < p) return N - p + k;
                return k - p;
            }();

            cout << xs[j] << '\n';
        }
    }

    return 0;
}
