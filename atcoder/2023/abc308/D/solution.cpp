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

static const set<char> Allowed{'s', 'n', 'u', 'k', 'e'};

constexpr char next_char(const char c) {
    switch (c) {
    case 's':
        return 'n';
    case 'n':
        return 'u';
    case 'u':
        return 'k';
    case 'k':
        return 'e';
    case 'e':
        return 's';
    default:
        assert(false && "invalid char");
        return '-';
    }
}

bool is_possible(const vector<string> &grid) {
    if (grid[0][0] != 's') return false;
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    vector<vector<bool>> visited(H, vector<bool>(W, false));
    queue<pii> q;
    q.emplace(0, 0);

    while (!q.empty()) {
        const auto u = q.front();
        const auto [ro, co] = u;
        q.pop();

        for (const auto &delta :
             vector<pii>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
            const auto v = u + delta;
            if (!in_bounds(v)) continue;

            const auto [ro_, co_] = v;
            if (visited[ro_][co_] ||
                next_char(grid[ro][co]) != grid[ro_][co_]) {
                continue;
            }

            if (ro_ == H - 1 && co_ == W - 1) return true;
            visited[ro_][co_] = true;
            q.emplace(ro_, co_);
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    const auto yes = is_possible(grid);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
