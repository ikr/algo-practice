#include "lest.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace atcoder {

struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(
                         result.begin(), result.end(),
                         [&](const std::vector<int> &v) { return v.empty(); }),
                     result.end());
        return result;
    }

  private:
    int _n;
    std::vector<int> parent_or_size;
};

} // namespace atcoder

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

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
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

vi component(const int N, const vi &xs, const vi &ys) {
    atcoder::dsu cs(N);

    for (int i = 0; i < sz(xs); ++i) {
        cs.merge(xs[i], ys[i]);
    }

    const auto ans = cs.groups();
    return *max_element(begin(ans), end(ans),
                        [](const vi &a, const vi &b) { return sz(a) < sz(b); });
}

vi topo_sort(const vvi &g, const vi c) {
    if (sz(c) == 1) return c;

    map<int, bool> discovered;
    for (const auto x : c) discovered[x] = false;

    vi ans;

    function<void(int)> recur;
    recur = [&](const int u) {
        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            discovered[v] = true;
            recur(v);
            ans.push_back(v);
        }
    };

    for (int i = 0; i < sz(c); ++i) {
        if (discovered[c[i]]) continue;
        recur(c[i]);
        discovered[c[i]] = true;
    }

    reverse(begin(ans), end(ans));
    return ans;
}

struct JoinAClub final {
    vi maximumClub(const int N, const vi &xs, const vi &ys) const {
        vvi g(N, vi{});
        for (int i = 0; i < sz(xs); ++i) {
            g[xs[i]].push_back(ys[i]);
            g[ys[i]].push_back(xs[i]);
        }
        return topo_sort(g, component(N, xs, ys));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = JoinAClub{}.maximumClub(5, {}, {});
        const auto expected = vi{0};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = JoinAClub{}.maximumClub(4, {0, 0, 0, 1, 1, 3}, {1, 2, 3, 3, 2, 2});
        const auto expected = vi{2, 0, 1, 3};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = JoinAClub{}.maximumClub(6, {0, 1, 2, 5}, {3, 3, 3, 3});
        const auto expected = vi{2, 3, 0, 1, 5};
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = JoinAClub{}.maximumClub(47, {0, 4, 6, 6, 42}, {13, 7, 7, 23, 15});
        const auto expected = vi{4, 7, 6, 23};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
