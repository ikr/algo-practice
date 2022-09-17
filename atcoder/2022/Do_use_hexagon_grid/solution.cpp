#include <atcoder/dsu>
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

static const vector<pii> DS{{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};

int num_components(const vector<pii> XY) {
    map<pii, int> idx;
    for (int i = 0; i < sz(XY); ++i) {
        idx.emplace(XY[i], i);
    }

    atcoder::dsu cs(sz(XY));

    for (int u = 0; u < sz(XY); ++u) {
        for (const auto &delta : DS) {
            const auto it = idx.find(XY[u] + delta);
            if (it != cend(idx)) {
                const auto v = it->second;
                cs.merge(u, v);
            }
        }
    }

    return sz(cs.groups());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pii> XY(N);
    for (auto &[x, y] : XY) {
        cin >> x >> y;
    }

    cout << num_components(XY) << '\n';
    return 0;
}
