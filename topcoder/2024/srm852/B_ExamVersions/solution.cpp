#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct ExamVersions final {
    vector<string> distribute(const int H, const int W, const int N) const {
        const auto in_bounds = [&](const int r, const int c) {
            return 0 <= r && r < H && 0 <= c && c < W;
        };

        vector<string> result(H, string(W, ' '));
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                set<char> taken;

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) continue;
                        if (!in_bounds(r + dr, c + dc)) continue;
                        if (result[r + dr][c + dc] == ' ') continue;
                        taken.insert(result[r + dr][c + dc]);
                    }
                }

                for (int i = 0; i < N; ++i) {
                    const auto ch = static_cast<char>('A' + i);
                    if (!taken.count(ch)) {
                        result[r][c] = ch;
                        break;
                    }
                }
                if (result[r][c] == ' ') return {};
            }
        }
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ExamVersions{}.distribute(1, 8, 25);
        const auto expected = vector<string>{string{"ABABABAB"}};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ExamVersions{}.distribute(3, 5, 7);
        const auto expected = vector<string>{string{"ABABA"},
                                             string{"CDCDC"},
                                             string{"ABABA"}};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
