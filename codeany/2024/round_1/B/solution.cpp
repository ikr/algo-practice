#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

pair<int, int> max_lr_deltas(const string &algo) {
    int dl{};
    int dr{};
    int cur{};
    for (const auto command : algo) {
        if (command == 'L') {
            --cur;
            dl = min(dl, cur);
        } else {
            assert(command == 'R');
            ++cur;
            dr = max(dr, cur);
        }
    }
    return {dl, dr};
}

bool survives(const pair<int, int> dldr, const set<int> &blocks, const int i0) {
    const auto [dl, dr] = dldr;
    const auto lo = *prev(blocks.lower_bound(i0));
    const auto hi = *blocks.upper_bound(i0);
    return lo < i0 + dl && i0 + dr < hi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    string room;
    cin >> room;
    assert(sz(room) == n);

    string algo;
    cin >> algo;
    assert(sz(algo) == m);

    set<int> blocks{-1, n};
    vector<int> robots;
    for (int i = 0; i < sz(room); ++i) {
        if (room[i] == '#') {
            blocks.insert(i);
        } else if (room[i] == 'D') {
            robots.push_back(i);
        }
    }

    const auto dldr = max_lr_deltas(algo);
    vector<int> survivior_coords;
    for (const auto i0 : robots) {
        if (survives(dldr, blocks, i0)) {
            survivior_coords.push_back(i0 + 1);
        }
    }

    cout << sz(survivior_coords) << '\n';
    cout << survivior_coords << '\n';
    return 0;
}
