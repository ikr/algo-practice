#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using Words = vector<string>;
using Groups = vector<Words>;

string sorted_letters(string word) {
    sort(word.begin(), word.end());
    return word;
}

Groups value_groups(const multimap<string, string> &wmap) {
    Groups result;
    string last_key = "Z";

    for (const auto i : wmap) {
        if (i.first != last_key) {
            result.push_back(Words{});
            last_key = i.first;
        }

        result.back().push_back(i.second);
    }

    return result;
}

struct Solution final {
    Groups groupAnagrams(const Words &ws) const {
        multimap<string, string> words_by_sorted_letters;

        transform(
            ws.begin(), ws.end(),
            inserter(words_by_sorted_letters, words_by_sorted_letters.end()),
            [](const string &w) { return make_pair(sorted_letters(w), w); });

        return value_groups(words_by_sorted_letters);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("empty") {
        const Groups actual = Solution().groupAnagrams(Words{});
        const Groups expected = Groups{};
        EXPECT(actual == expected);
    },
    CASE("problem statement example") {
        const Groups actual = Solution().groupAnagrams(Words{"eat","tea","tan","ate","nat","bat"});

        const Groups expected = Groups{
            {"bat"},
            {"eat","tea","ate"},
            {"nat","tan"}
        };

        EXPECT(actual == expected);
    },
    CASE("degenerate case") {
        const Groups actual = Solution().groupAnagrams(Words{"a"});
        const Groups expected = Groups{{"a"}};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
