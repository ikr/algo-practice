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

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << x.first << ' ' << x.second;
    return os;
}

int manhattan(const pii p1, const pii p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

pair<pii, pii> place_yoyos(const int H, const int W, const pii p0) {
    if (H == 1) return {{1, 1}, {1, W}};
    if (W == 1) return {{1, 1}, {H, 1}};

    priority_queue<pair<int, pii>> pq1;

    const pii lt{1, 1};
    const pii rt{1, W};
    const pii rb{H, W};
    const pii lb{H, 1};

    for (const auto e : {lt, rt, rb, lb}) {
        pq1.emplace(manhattan(p0, e), e);
    }

    const auto a = pq1.top().second;

    priority_queue<pair<int, pii>> pq2;
    for (const auto e : {lt, rt, rb, lb}) {
        pq2.emplace(manhattan(a, e) + manhattan(e, p0), e);
    }

    const auto b = pq2.top().second;
    return {a, b};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int H, W, ro0, co0;
        cin >> H >> W >> ro0 >> co0;

        const auto [p1, p2] = place_yoyos(H, W, {ro0, co0});
        cout << p1 << ' ' << p2 << '\n';
    }

    return 0;
}
