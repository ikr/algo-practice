#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

constexpr bool same_color(const pi p1, const pi p2) {
    return (p1.first + p1.second) % 2 == (p2.first + p2.second) % 2;
}

constexpr bool same_diag(const pi p1, const pi p2) {
    const auto [a, b] = p1;
    const auto [c, d] = p2;
    return a + b == c + d || a - b == c - d;
}

constexpr int mhtn(const pi p1, const pi p2) {
    const auto [a, b] = p1;
    const auto [c, d] = p2;
    return abs(a - c) + abs(b - d);
}

vector<pi> mhtn_3_neighs(const pi p) {
    vector<pi> ans;
    ans.reserve(16);

    for (int dr = -3; dr <= 3; ++dr) {
        for (int dc = -3; dc <= 3; ++dc) {
            const pi p_ = p + pi{dr, dc};
            if (p_ != p && mhtn(p, p_) <= 3) ans.push_back(p_);
        }
    }

    return ans;
}

int min_moves(const pi p1, const pi p2) {
    if (p1 == p2) return 0;
    if (mhtn(p1, p2) <= 3 || same_diag(p1, p2)) return 1;
    if (mhtn(p1, p2) <= 6) return 2;

    for (const auto p2_ : mhtn_3_neighs(p2)) {
        if (same_diag(p1, p2_)) return 2;
    }

    return same_color(p1, p2) ? 2 : 3;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    pi p1, p2;
    cin >> p1.first >> p1.second >> p2.first >> p2.second;

    cout << min_moves(p1, p2) << '\n';
    return 0;
}
