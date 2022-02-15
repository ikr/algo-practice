#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <tuple>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<int> suggest_missing(const vector<vector<int>> &grid) {
    map<int, int> fs;

    for (const auto &row : grid) {
        for (const auto x : row) {
            if (x == -1) continue;
            ++fs[x];
        }
    }

    if (sz(fs) == 1 && cbegin(fs)->first == 0) return 0;

    const auto [evs, ods, one_odd] = [&]() -> tuple<int, int, int> {
        int a{};
        int b{};
        int c = -1;

        for (const auto [x, f] : fs) {
            if (f % 2 == 0) {
                ++a;
            } else {
                ++b;
                c = x;
            }
        }

        return {a, b, c};
    }();

    if (ods == 1) {
        assert(one_odd > 0);
        assert(one_odd % 2);
        return one_odd;
    }

    return nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<vector<int>> grid(H, vector<int>(W));
    for (auto &row : grid) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    const auto result = suggest_missing(grid);
    if (result) {
        cout << "YES\n" << *result << '\n';
    } else {
        cout << "NO\n";
    }
    return 0;
}
