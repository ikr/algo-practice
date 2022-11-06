#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using tri = tuple<int, int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const map<char, int> BASE_INDEX{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

int bases_distance(const char x, const char y) {
    assert(BASE_INDEX.count(x));
    assert(BASE_INDEX.count(y));

    auto ix = BASE_INDEX.at(x);
    auto iy = BASE_INDEX.at(y);
    if (ix > iy) swap(ix, iy);

    return min(iy - ix, ix + 4 - iy);
}

int strands_distance(const string &xs, const string &ys) {
    assert(sz(xs) == sz(ys));
    int result{};

    for (int i = 0; i < sz(xs); ++i) {
        result += bases_distance(xs[i], ys[i]);
    }

    return result;
}

priority_queue<tri> edges_by_lightness(const vector<string> &dst) {
    priority_queue<tri> q;

    for (int u = 0; u < sz(dst) - 1; ++u) {
        for (int v = u + 1; v < sz(dst); ++v) {
            const auto d = strands_distance(dst[u], dst[v]);
            q.emplace(-d, u, v);
        }
    }

    return q;
}

int min_ops(const vector<string> &dst) {
    auto q = edges_by_lightness(dst);
    atcoder::dsu cs(sz(dst));
    int result{};

    while (!q.empty()) {
        const auto [d, u, v] = q.top();
        q.pop();
        if (cs.same(u, v)) continue;

        cs.merge(u, v);
        result += -d;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L;
    cin >> N >> L;

    vector<string> dst(N);
    for (auto &xs : dst) cin >> xs;
    dst.push_back(string(L, 'A'));

    cout << min_ops(dst) << '\n';
    return 0;
}
