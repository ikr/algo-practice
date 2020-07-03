#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using pi = pair<int, int>;
using vpi = vector<pi>;

static constexpr int SZ = 8;

bool can_place(const vpi &placed, const pi coord) {
    const auto [r, c] = coord;
    for (const auto [r0, c0] : placed) {
        if (c0 == c || abs(r0 - r) == abs(c0 - c)) return false;
    }
    return true;
}

int num_ways(const vs &rows, vpi &placed) {
    int ans = 0;

    for (int r = placed.empty() ? 0 : placed.back().first + 1; r < SZ; ++r) {
        for (int c = 0; c != SZ; ++c) {
            if (can_place(placed, {r, c})) {
                if (rows[r][c] == '*') continue;

                if (placed.size() == SZ - 1) {
                    ++ans;
                } else {
                    placed.emplace_back(r, c);
                    ans += num_ways(rows, placed);
                    placed.pop_back();
                }
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vs rows(SZ, "");
    for (auto &s : rows) cin >> s;

    vpi placed;
    cout << num_ways(rows, placed) << '\n';

    return 0;
}
