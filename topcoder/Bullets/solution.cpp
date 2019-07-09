#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Bullets final {
	 int match(const vector<string> &guns, string bullet) const {
     	bullet = bullet + bullet;

        for (size_t i = 0; i != guns.size(); ++i) {
            if (bullet.find(guns[i]) != string::npos) return i;
        }

        return -1;
     }
};

// clang-format off
const lest::test tests[] = {
    CASE("one") {
        const auto actual = Bullets().match({"| | | |","|| || |"," ||||  "}, "|| || |");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char** argv) {
    return lest::run(tests, argc, argv);
}
