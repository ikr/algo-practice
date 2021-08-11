#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using tri = tuple<int, int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool in_bounds(const int H, const int W, const pii x) {
    const auto [ro, co] = x;
    return ro >= 0 && ro < H && co >= 0 && co < W;
}

vector<pii> adjacent(const int H, const int W, const pii x) {
    const auto [ro, co] = x;
    vector<pii> ans;

    if (in_bounds(H, W, {ro - 1, co})) ans.emplace_back(ro - 1, co);
    if (in_bounds(H, W, {ro, co + 1})) ans.emplace_back(ro, co + 1);
    if (in_bounds(H, W, {ro + 1, co})) ans.emplace_back(ro + 1, co);
    if (in_bounds(H, W, {ro, co - 1})) ans.emplace_back(ro, co - 1);

    return ans;
}

vector<pii> adjacent_with_diag(const int H, const int W, const pii x) {
    const auto [ro, co] = x;
    auto ans = adjacent(H, W, x);

    if (in_bounds(H, W, {ro - 1, co - 1})) ans.emplace_back(ro - 1, co - 1);
    if (in_bounds(H, W, {ro - 1, co + 1})) ans.emplace_back(ro - 1, co + 1);
    if (in_bounds(H, W, {ro + 1, co + 1})) ans.emplace_back(ro + 1, co + 1);
    if (in_bounds(H, W, {ro + 1, co - 1})) ans.emplace_back(ro + 1, co - 1);

    return ans;
}

int min_punches(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const pii dest{H - 1, W - 1};

    vector<vector<bool>> visited(H, vector(W, false));

    deque<tri> q;
    q.emplace_front(0, 0, 0);

    while (!q.empty()) {
        const auto [cost, ro0, co0] = q.front();
        q.pop_front();

        if (visited[ro0][co0]) continue;
        visited[ro0][co0] = true;

        for (const auto v : adjacent(H, W, pii{ro0, co0})) {
            const auto [ro, co] = v;
            if (v == dest) return cost;

            if (grid[ro][co] == '.') {
                q.emplace_front(cost, ro, co);
                continue;
            }

            assert(grid[ro][co] == '#');
            q.emplace_back(cost + 1, ro, co);

            for (const auto v_ : adjacent_with_diag(H, W, v)) {
                const auto [ro_, co_] = v_;
                q.emplace_back(cost + 1, ro_, co_);
            }
        }
    }

    assert(false && "min_punches return");
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H, string(W, ' '));
    for (auto &row : grid) {
        cin >> row;
    }

    cout << min_punches(grid) << '\n';
    return 0;
}
