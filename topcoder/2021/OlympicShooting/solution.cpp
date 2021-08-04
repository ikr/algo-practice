#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
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

struct Result final {
    int i;
    vi chunk_hits;
    int hits;
    string xs;
};

Result as_result(const int i, const string &xs) {
    assert(sz(xs) % 25 == 0);
    const int chunks_num = sz(xs) / 25;
    vi chunk_hits(chunks_num, 0);

    for (int j = 0; j < chunks_num; ++j) {
        const auto sub = xs.substr(j * 25, 25);
        chunk_hits[j] = inof(count(cbegin(sub), cend(sub), '1'));
    }

    return Result{i, chunk_hits,
                  accumulate(cbegin(chunk_hits), cend(chunk_hits), 0), xs};
}

bool is_less_on_chunk_hits(const vi &xs, const vi &ys) {
    assert(sz(xs) == sz(ys));
    for (int i = sz(xs) - 1; i >= 0; --i) {
        if (xs[i] < ys[i]) return true;
        if (xs[i] > ys[i]) return false;
    }
    return false;
}

bool is_less(const Result &a, const Result &b) {
    if (a.hits < b.hits) return true;
    if (a.hits > b.hits) return false;

    if (is_less_on_chunk_hits(a.chunk_hits, b.chunk_hits)) return true;
    if (is_less_on_chunk_hits(b.chunk_hits, a.chunk_hits)) return false;

    assert(b.chunk_hits == a.chunk_hits);
    assert(sz(a.xs) == sz(b.xs));

    if (a.xs == b.xs) return a.i > b.i;

    for (int i = sz(a.xs) - 1; i >= 0; --i) {
        if (a.xs[i] < b.xs[i]) return true;
        if (a.xs[i] > b.xs[i]) return false;
    }

    return false;
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
    CASE("pre-one") {
        const auto r0 = as_result(0, "11111111111011111111111110000000000000000000010000");
        const auto r1 = as_result(1, "11111111111111111111111000000000000000000000001000");
        const auto r2 = as_result(2, "11111111111111111111101110000000000000000000000100");
        const auto r3 = as_result(3, "11111111111111111111111110000000000000000000000010");
        const auto r4 = as_result(4, "11111111111111111111101110000000000000000000000001");

        EXPECT(!is_less(r0, r1));

        EXPECT(is_less(r1, r0));
        EXPECT(is_less(r1, r2));
        EXPECT(is_less(r1, r4));
        EXPECT(is_less(r1, r3));

        EXPECT(is_less(r0, r3));
        EXPECT(is_less(r0, r4));
        EXPECT(is_less(r0, r2));

        EXPECT(is_less(r2, r4));
        EXPECT(is_less(r2, r3));

        EXPECT(is_less(r4, r3));
    },
    CASE("pre-two") {
        const auto r0 = as_result(0, "11111111111011111111111110000000000000000000000100");
        const auto r1 = as_result(1, "11111111111111111111111000000000000000000000011000");
        const auto r2 = as_result(2, "11111111111111111111101110000000000000000000000100");
        const auto r3 = as_result(3, "11111111111111111111111110000000000000000000000010");
        const auto r4 = as_result(4, "11111111111111111111101110000000000000000000000001");

        EXPECT(is_less(r2, r0));
        EXPECT(is_less(r2, r4));
        EXPECT(is_less(r2, r1));
        EXPECT(is_less(r2, r3));

        EXPECT(is_less(r0, r1));
        EXPECT(is_less(r0, r3));
        EXPECT(is_less(r0, r4));

        EXPECT(is_less(r4, r1));
        EXPECT(is_less(r4, r3));

        EXPECT(is_less(r1, r3));

        EXPECT(!is_less(r1, r0));
    },
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
