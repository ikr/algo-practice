#include <bits/stdc++.h>
using namespace std;

static constexpr int L = 6;

int remaining_blacks(const vector<string> &rows, const int rbits,
                     const int cbits) {
    const int H = rows.size();
    const int W = rows[0].size();

    const bitset<L> rbs(rbits);
    const bitset<L> cbs(cbits);

    int ans = 0;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (rbs.test(r) || cbs.test(c)) continue;
            if (rows[r][c] == '#') ++ans;
        }
    }
    return ans;
}

int choices(const vector<string> &rows, const int K) {
    const int H = rows.size();
    const int W = rows[0].size();

    int ans = 0;

    for (int rbits = 0; rbits <= (1 << H) - 1; ++rbits) {
        for (int cbits = 0; cbits <= (1 << W) - 1; ++cbits) {
            if (remaining_blacks(rows, rbits, cbits) == K) ++ans;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W, K;
    cin >> H >> W >> K;
    vector<string> rows(H, "");
    for (auto &row : rows) cin >> row;

    cout << choices(rows, K) << '\n';

    return 0;
}
