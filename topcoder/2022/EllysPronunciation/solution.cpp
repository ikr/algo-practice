#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

bool is_vowel(const char x) {
    static const set<char> vs{'a', 'e', 'i', 'o', 'u'};
    return vs.count(x);
}

struct EllysPronunciation final {
    int getGood(const vector<string> &ws) const {
        return inof(count_if(xbegin(ws), xend(ws), [](const string &w) {
            const auto vs = count_if(xbegin(w), xend(w), is_vowel);
            const auto cs = sz(w) - vs;
            return vs == cs;
        }));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = EllysPronunciation{}.getGood({"wrath", "allure", "vorliebe", "abneigung", "amor", "voulez", "ecoeurement", "odiar"});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = EllysPronunciation{}.getGood({"schornsteinfeger", "schmetterling", "lohnsteuerabzugsbescheinigung", "shifffahrt", "deutsch", "ist", "die", "schoenste", "sprache", "auf", "der", "welt"});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
