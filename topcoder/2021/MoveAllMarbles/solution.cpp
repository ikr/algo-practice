#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

void push_back_all(vi &dst, const array<int, 4> &src) {
    dst.insert(end(dst), src.cbegin(), src.cend());
}

struct MoveAllMarbles final {
    vi move(const int h, const int w, const int n) const {
        vvi rows(h, vi(w, 0));
        rows[0][0] = n;

        vi ans;
        ans.reserve((h + w) * n);

        const auto is_free = [&](const int ro, const int co) -> bool {
            if (ro < 0 || ro >= h || co < 0 || co >= w) return false;

            if (ro == h - 1 && co == w - 1) {
                return !rows[0][0];
            }

            return rows[ro][co] == 0;
        };

        while (rows.back().back() != n) {
            for (int ro = 0; ro < h; ++ro) {
                for (int co = 0; co < w; ++co) {
                    if (ro == h - 1 && co == w - 1) continue;

                    if (rows[ro][co]) {
                        if (is_free(ro + 1, co)) {
                            --rows[ro][co];
                            ++rows[ro + 1][co];
                            push_back_all(ans, {ro, co, ro + 1, co});
                        } else if (is_free(ro, co + 1)) {
                            --rows[ro][co];
                            ++rows[ro][co + 1];
                            push_back_all(ans, {ro, co, ro, co + 1});
                        }
                    }
                }
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MoveAllMarbles{}.move(2, 3, 1);
        const auto expected = vi{0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 2};
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = MoveAllMarbles{}.move(1, 3, 1);
        const auto expected = vi{0, 0, 0, 1, 0, 1, 0, 2};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
