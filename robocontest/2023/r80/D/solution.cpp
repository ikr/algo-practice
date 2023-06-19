#include <bits/stdc++.h>
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

static constexpr int INF = 1'000'000'000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) cin >> row;

    vector<vector<int>> FT(H, vector(W, INF));
    queue<pii> fq;

    pii src{-1, -1};
    pii dst{-1, -1};
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            switch (grid[ro][co]) {
            case 'S':
                src = {ro, co};
                break;
            case 'D':
                dst = {ro, co};
                break;
            case '*':
                FT[ro][co] = 0;
                fq.emplace(ro, co);
                break;
            }
        }
    }

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    while (!fq.empty()) {
        const auto u0 = fq.front();
        fq.pop();

        const auto [ro0, co0] = u0;
        assert(FT[ro0][co0] != INF);

        for (const auto &delta : {pii{-1, 0}, pii{0, 1}, pii{1, 0}, {0, -1}}) {
            const auto v = u0 + delta;
            if (!in_bounds(v)) continue;
            const auto [ro, co] = v;
            if (grid[ro][co] == 'X' || grid[ro][co] == 'D' ||
                FT[ro][co] != INF) {
                continue;
            }

            FT[ro][co] = FT[ro0][co0] + 1;
            fq.emplace(ro, co);
        }
    }

    const auto tt = [&]() -> int {
        queue<pii> q;
        q.push(src);

        vector<vector<int>> T(H, vector(W, INF));
        T[src.first][src.second] = 0;

        while (!q.empty()) {
            const auto u0 = q.front();
            q.pop();

            const auto [ro0, co0] = u0;
            assert(T[ro0][co0] != INF);

            for (const auto &delta :
                 {pii{-1, 0}, pii{0, 1}, pii{1, 0}, {0, -1}}) {
                const auto v = u0 + delta;
                if (!in_bounds(v)) continue;
                const auto [ro, co] = v;

                if (dst == v) {
                    if (T[ro][co] != INF || T[ro0][co0] + 1 >= FT[ro][co]) {
                        continue;
                    }
                } else if (grid[ro][co] == 'X' || T[ro][co] != INF ||
                           T[ro0][co0] + 1 >= FT[ro][co]) {
                    continue;
                }

                T[ro][co] = T[ro0][co0] + 1;
                q.emplace(ro, co);
            }
        }

        return T[dst.first][dst.second];
    }();

    if (tt == INF) {
        cout << "KARANTIN\n";
    } else {
        cout << tt << '\n';
    }
    return 0;
}
