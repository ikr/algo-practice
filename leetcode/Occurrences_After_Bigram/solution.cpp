#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

vector<string> words(const string &text) {
    istringstream iss{text};
    vector<string> result;

    copy(istream_iterator<string>(iss), istream_iterator<string>(),
         back_inserter(result));

    return result;
}

struct Solution final {
    vector<string> findOcurrences(const string &text, const string &first,
                                  const string &second) const {
        const auto ws = words(text);
        vector<string> result;

        for (auto i = ws.begin(); i != ws.end(); ++i) {
            const string a = *i;
            const string b = (i + 1 == ws.end() ? "" : *(i + 1));

            const string c =
                (i + 1 == ws.end() || i + 2 == ws.end() ? "" : *(i + 2));

            if (c.size() && a == first && b == second) result.push_back(c);
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().findOcurrences(
            "alice is a good girl she is a good student", "a", "good");
        const auto expected = vector<string>{"girl","student"};
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().findOcurrences(
            "we will we will rock you", "we", "will");
        const auto expected = vector<string>{"we","rock"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
