#include "lest.hpp"
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

using Graph = multimap<int, int>;

static constexpr ll M = (1LL << 31);

Graph build_graph(const int n, const int th, ll st) {
    const auto rnd = [&]() -> ll {
        st = ((st * 1103515245) % M + 12345) % M;
        return st % 100;
    };

    Graph ans;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (rnd() < th) {
                ans.emplace(i, j);
            } else {
                ans.emplace(j, i);
            }
        }
    }

    return ans;
}

using Quad = tuple<int, int, int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const Quad &x) {
    os << '(' << get<0>(x) << ' ' << get<1>(x) << ' ' << get<2>(x) << ' '
       << get<3>(x) << ')';
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

vector<Quad> search_quads(const int n, const Graph &g, const int src) {
    assert(src < n);
    vector<Quad> ans;

    vector<bool> discovered(n, false);
    discovered[src] = true;

    function<void(vi)> dfs;
    dfs = [&](vi path) {
        if (sz(path) == 4) {
            sort(begin(path), end(path));
            cerr << path << '\n';
            ans.emplace_back(path[0], path[1], path[2], path[3]);
            return;
        }

        const int u = path.back();
        const auto range = g.equal_range(u);
        for (auto it = range.first; it != range.second; ++it) {
            const int v = it->second;
            if (discovered[v]) continue;

            discovered[v] = true;
            path.push_back(v);
            dfs(path);
        }
    };

    dfs({src});
    return ans;
}

struct MarriageAndCirclingChallenge final {
    ll solve(const int n, const int th, const int st) const {
        const auto g = build_graph(n, th, st);
        set<Quad> qs;

        for (int i = 0; i < n; ++i) {
            const auto res = search_quads(n, g, i);
            qs.insert(res.cbegin(), res.cend());
        }

        return sz(qs);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MarriageAndCirclingChallenge{}.solve(10, 0, 12345);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = MarriageAndCirclingChallenge{}.solve(5, 50, 47);
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = MarriageAndCirclingChallenge{}.solve(9, 20, 1234567);
        const auto expected = 29;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
