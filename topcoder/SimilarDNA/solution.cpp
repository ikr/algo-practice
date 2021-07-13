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

static const string YES{"similar"};
static const string NO{"distinct"};

string solve(const string &a, const string &b) {
    function<bool(int, int, int)> recur;
    recur = [&](const int ops, const int i, const int j) -> bool {
        if (i >= sz(a) && j >= sz(b)) return true;

        if (i >= sz(a)) {
            if (!ops) return false;
            return recur(ops - 1, i, j + 1);
        }

        if (j >= sz(b)) {
            if (!ops) return false;
            return recur(ops - 1, i + 1, j);
        }

        if (a[i] == b[j]) return recur(ops, i + 1, j + 1);
        if (ops <= 0) return false;

        return recur(ops - 1, i + 1, j + 1) || recur(ops - 1, i + 1, j) ||
               recur(ops - 1, i, j + 1);
    };

    return recur(2, 0, 0) ? YES : NO;
}

struct SimilarDNA final {
    string areSimilar(const string &a, const string &b) const {
        if (a == b) return YES;
        if (abs(sz(a) - sz(b)) > 2) return NO;

        return sz(a) <= sz(b) ? solve(a, b) : solve(b, a);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SimilarDNA{}.areSimilar("AAAAA", "AACAACA");
        const auto expected = "similar";
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SimilarDNA{}.areSimilar("AACAACA", "AAAAA");
        const auto expected = "similar";
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = SimilarDNA{}.areSimilar("AACAACA", "AAGAATA");
        const auto expected = "similar";
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = SimilarDNA{}.areSimilar("CGATCGAT", "CATCGAG");
        const auto expected = "similar";
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = SimilarDNA{}.areSimilar("CGATCGAT", "CGATCGAT");
        const auto expected = "similar";
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = SimilarDNA{}.areSimilar("CGATATATAGGA", "GGATATACCATA");
        const auto expected = "distinct";
        EXPECT(actual == expected);
    },
    CASE("Example 6") {
        const auto actual = SimilarDNA{}.areSimilar("AAAAA", "AA");
        const auto expected = "distinct";
        EXPECT(actual == expected);
    },
    CASE("A and AG") {
        const auto actual = SimilarDNA{}.areSimilar("A", "AG");
        const auto expected = "similar";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
