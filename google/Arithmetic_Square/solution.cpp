#include <bits/stdc++.h>
#include <queue>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr ll average(const ll x, const ll y) { return (x + y) / 2LL; }

constexpr bool are_in_progr(const ll x, const ll y, const ll z) {
    return ((x + z) % 2 == 0) && (y == average(x, z));
}

int guaranteed(const vvll &grid) {
    int ans = 0;

    for (int i : {0, 2}) {
        if (are_in_progr(grid[i][0], grid[i][1], grid[i][2])) {
            ++ans;
        }

        if (are_in_progr(grid[0][i], grid[1][i], grid[2][i])) {
            ++ans;
        }
    }

    return ans;
}

int constructed(const vvll &grid, const ll mid) {
    int ans = 0;

    if (are_in_progr(grid[0][0], mid, grid[2][2])) {
        ++ans;
    }

    if (are_in_progr(grid[2][0], mid, grid[0][2])) {
        ++ans;
    }

    if (are_in_progr(grid[1][0], mid, grid[1][2])) {
        ++ans;
    }

    if (are_in_progr(grid[0][1], mid, grid[2][1])) {
        ++ans;
    }

    return ans;
}

int solve(const vvll &grid) {
    vll mid{average(grid[0][0], grid[2][2]), average(grid[2][0], grid[0][2]),
            average(grid[1][0], grid[1][2]), average(grid[0][1], grid[2][1])};

    priority_queue<int> pq;
    for (const auto m : mid) {
        pq.push(constructed(grid, m));
    }

    return guaranteed(grid) + pq.top();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        vvll grid(3, vll(3, 0));
        for (auto &x : grid[0]) cin >> x;
        cin >> grid[1][0] >> grid[1][2];
        for (auto &x : grid[2]) cin >> x;

        cout << "Case #" << i << ": " << solve(grid) << '\n';
    }

    return 0;
}
