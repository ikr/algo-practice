#include <array>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    int P{};
    array<int, 4> sq{};
    for (const auto a : xs) {
        ++sq[0];

        for (int i = sz(sq) - 1; i >= 0; --i) {
            if (i + a < sz(sq)) {
                sq[i + a] += sq[i];
            } else {
                P += sq[i];
            }

            sq[i] = 0;
        }
    }

    cout << P << '\n';
    return 0;
}
