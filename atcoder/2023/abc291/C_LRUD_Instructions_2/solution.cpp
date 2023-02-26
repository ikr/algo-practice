#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

pii delta(const char cmd) {
    if (cmd == 'R') return {1, 0};
    if (cmd == 'L') return {-1, 0};
    if (cmd == 'U') return {0, 1};
    assert(cmd == 'D');
    return {0, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    set<pii> seen{{0, 0}};
    pii xy{0, 0};

    const auto ans = [&]() -> string {
        for (const auto cmd : xs) {
            xy = xy + delta(cmd);
            if (seen.count(xy)) return "Yes";
            seen.insert(xy);
        }
        return "No";
    }();

    cout << ans << '\n';
    return 0;
}
