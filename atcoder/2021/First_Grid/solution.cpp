#include <bits/stdc++.h>
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

bool in_bounds(const int ro, const int co) {
    return 0 <= ro && ro < 2 && 0 <= co && co < 2;
}

char safe_get(const vector<string> &grid, const int ro, const int co) {
    return in_bounds(ro, co) ? grid[ro][co] : '.';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    vector<string> grid(2, string(2, ' '));
    int blacks{};
    for (auto &row : grid) {
        cin >> row;
        blacks += count(cbegin(row), cend(row), '#');
    }

    const bool ok = [&]() -> bool {
        if (blacks > 2) return true;
        assert(blacks == 2);

        if (grid[0][0] == '#' && grid[1][1] == '#') return false;
        if (grid[0][1] == '#' && grid[1][0] == '#') return false;
        return true;
    }();

    cout << (ok ? "Yes" : "No") << '\n';
    return 0;
}
