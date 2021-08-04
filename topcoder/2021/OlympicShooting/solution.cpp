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

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }

string::const_iterator cend(const string &xs) { return xs.cend(); }

struct Chunk final {
    string xs;
    int hits;
};

struct Result final {
    int i;
    vector<Chunk> cs;
    int hits;
};

Chunk as_chunk(const string &xs) {
    assert(sz(xs) == 25);
    return Chunk{xs, inof(count(cbegin(xs), cend(xs), '1'))};
}

Result as_result(const int i, const string &xs) {
    assert(sz(xs) % 25 == 0);
    const int chunks_num = sz(xs) / 25;
    vector<Chunk> cs;

    for (int j = 0; j < chunks_num; ++j) {
        const auto sub = xs.substr(j * 25, 25);
        cs.push_back(as_chunk(sub));
    }

    int hits = 0;
    for (const auto &c : cs) {
        hits += c.hits;
    }
    return Result{i, cs, hits};
}

bool is_less(const Chunk &a, const Chunk &b) {
    if (a.hits < b.hits) return true;
    if (a.hits > b.hits) return false;

    assert(sz(a.xs) == sz(b.xs));

    auto ps = a.xs;
    reverse(begin(ps), end(ps));
    auto qs = b.xs;
    reverse(begin(qs), end(qs));

    return ps < qs;
}

bool is_less(const Result &a, const Result &b) {
    if (a.hits < b.hits) return true;
    if (a.hits > b.hits) return false;

    assert(sz(a.cs) == sz(b.cs));

    for (int i = sz(a.cs) - 1; i >= 0; --i) {
        if (a.cs[i].hits < b.cs[i].hits) return true;
    }

    for (int i = sz(a.cs) - 1; i >= 0; --i) {
        if (is_less(a.cs[i], b.cs[i])) return true;
    }

    return a.i > b.i;
}

vector<Result> as_results(const vector<string> &xss) {
    vector<Result> ans;
    for (int i = 0; i < sz(xss); ++i) {
        ans.push_back(as_result(i, xss[i]));
    }
    return ans;
}

struct OlympicShooting final {
    vi sort(const vector<string> &xss) const {
        const auto rs = as_results(xss);

        vi idx(sz(xss), 0);
        iota(begin(idx), end(idx), 0);

        std::sort(begin(idx), end(idx), [&rs](const int i, const int j) {
            return is_less(rs[i], rs[j]);
        });

        reverse(begin(idx), end(idx));
        return idx;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = OlympicShooting{}.sort({"1111111111101111111111111", "1111111111111111111111100", "1111111111111111111110111", "1111111111111111111111111", "1111111111111111111110111"});
        const auto expected = vi{3, 0, 2, 4, 1};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = OlympicShooting{}.sort({"11111111111011111111111110000000000000000000010000", "11111111111111111111111000000000000000000000001000", "11111111111111111111101110000000000000000000000100", "11111111111111111111111110000000000000000000000010", "11111111111111111111101110000000000000000000000001"});
        const auto expected = vi{3, 4, 2, 0, 1};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = OlympicShooting{}.sort({"11111111111011111111111110000000000000000000000100", "11111111111111111111111000000000000000000000011000", "11111111111111111111101110000000000000000000000100", "11111111111111111111111110000000000000000000000010", "11111111111111111111101110000000000000000000000001"});
        const auto expected = vi{3, 1, 4, 0, 2};
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = OlympicShooting{}.sort({"00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000", "00000000000000000000000000000000000000000000000000"});
        const auto expected = vi{0, 1, 2, 3, 4, 5};
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = OlympicShooting{}.sort({"10000000000000000000000000000000000000000000000000", "01000000000000000000000000000000000000000000000000"});
        const auto expected = vi{1, 0};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
