#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

using pii = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string best_trace(const vector<string> &grid) {
    const auto N = sz(grid);
    assert(sz(grid[0]) == N);

    string result(N, '0');

    for (int ro0 = 0; ro0 < N; ++ro0) {
        for (int co0 = 0; co0 < N; ++co0) {
            for (int dro = -1; dro <= 1; ++dro) {
                for (int dco = -1; dco <= 1; ++dco) {
                    if (!dro && !dco) continue;

                    string cur{grid[ro0][co0]};

                    for (int i = 1; i <= N - 1; ++i) {
                        const int ro = (((ro0 + dro * i) % N) + N) % N;
                        const int co = (((co0 + dco * i) % N) + N) % N;
                        cur += grid[ro][co];
                    }

                    result = max(result, cur);
                }
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> grid(N);
    for (auto &row : grid) cin >> row;

    cout << best_trace(grid) << '\n';
    return 0;
}
