#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, A, B;
    cin >> N >> A >> B;

    vector<string> grid(A * N, string(B * N, '.'));

    for (int ro = 0; ro < A * N; ++ro) {
        for (int co = 0; co < B * N; ++co) {
            if ((ro / A + co / B) % 2) {
                grid[ro][co] = '#';
            }
        }
    }

    for (const auto &row : grid) {
        cout << row << '\n';
    }

    return 0;
}
