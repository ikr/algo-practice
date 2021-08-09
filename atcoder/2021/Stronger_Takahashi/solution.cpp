#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using pii = pair<int, int>;

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

vector<pii> optimal_01_path(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const pii dest{H - 1, W - 1};

    vector<vector<bool>> discovered(H, vector<bool>(W, false));
    deque<pii> q;
    map<pii, pii> src;

    const auto reconstruct_path = [&]() -> vector<pii> {
        vector<pii> ans{dest};

        while (src.count(ans.back())) {
            ans.push_back(src.at(ans.back()));
        }

        reverse(begin(ans), end(ans));
        return ans;
    };

    discovered[0][0] = true;
    q.emplace_back(0, 0);

    for (;;) {
        const auto u = q.front();
        q.pop_front();

        for (const auto v : adjacent(H, W, u)) {
            const auto [ro, co] = v;
            if (discovered[ro][co]) continue;

            discovered[ro][co] = true;
            src[v] = u;
            if (v == dest) return reconstruct_path();

            if (grid[ro][co] == '.') {
                q.emplace_front(ro, co);
            } else {
                assert(grid[ro][co] == '#');
                q.emplace_back(ro, co);
            }
        }
    }
}

int chebyshev(const pii &x, const pii &y) {
    return max(abs(x.first - y.first), abs(x.second - y.second));
}

bool all_in_2x2_box(const vector<pii> &xs) {
    for (int i = 0; i < sz(xs) - 1; ++i) {
        for (int j = i + 1; i < sz(xs); ++j) {
            if (chebyshev(xs[i], xs[j]) > 1) return false;
        }
    }

    return true;
}

int walls_num(const vector<string> &grid, const vector<pii> &xs) {
    return inof(count_if(cbegin(xs), cend(xs), [&grid](const pii x) {
        return grid[x.first][x.second] == '#';
    }));
}

int distinct_num(vector<pii> xs) { return sz(set<pii>(cbegin(xs), cend(xs))); }

int punch_coverage_size(const vector<string> &grid, const vector<pii> &p) {
    int ans = 0;

    for (int i = 0; i < sz(p);) {
        const auto x = p[i];
        const auto y = i + 1 < sz(p) ? p[i + 1] : p[i];

        {
            const auto z = i + 2 < sz(p) ? p[i + 2] : p[i];
            const vector<pii> xs{x, y, z};
            const auto wn = walls_num(grid, xs);

            if (((wn == 3) || (distinct_num(xs) == 3 &&
                               grid[y.first][y.second] == '.' && wn == 2)) &&
                all_in_2x2_box(xs)) {
                ++ans;
                i += 3;
                continue;
            }
        }

        if (walls_num(grid, {x, y}) == 2) {
            ++ans;
            i += 2;
            continue;
        }

        if (grid[x.first][x.second] == '#') {
            ++ans;
        }

        ++i;
    }

    return ans;
}

int min_punches(const vector<string> &grid) {
    return punch_coverage_size(grid, optimal_01_path(grid));
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
