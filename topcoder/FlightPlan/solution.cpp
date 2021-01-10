#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Coord = tuple<int, int, int>;

struct UnitCosts final {
    int cup;
    int cdn;
    int clr;
};

constexpr ll r_of(const Coord &coord) { return get<0>(coord); }
constexpr ll c_of(const Coord &coord) { return get<1>(coord); }
constexpr ll h_of(const Coord &coord) { return get<2>(coord); }

ll direct_flight_cost(const UnitCosts &unit_costs, const Coord &a,
                      const Coord &b) {
    return (h_of(a) < h_of(b) ? (h_of(b) - h_of(a)) * unit_costs.cup
                              : (h_of(a) - h_of(b)) * unit_costs.cdn) +
           abs(r_of(a) - r_of(b)) + abs(c_of(a) - c_of(b));
}

struct FlightPlan final {
    ll fly(const int R, const int C, const vector<int> &H, const int cup,
           const int cdn, const int clr) const {
        const ll max_h = *max_element(H.cbegin(), H.cend());
        const UnitCosts unit_costs{cup, cdn, clr};

        const auto h_at = [&H, C](const int r, const int c) {
            return H[r * C + c];
        };

        const Coord dest{R - 1, C - 1, h_at(R - 1, C - 1)};

        vector<vector<vector<ll>>> costs(
            R, vector<vector<ll>>(C, vector<ll>(max_h + 1, -1)));
        costs[0][0][h_at(0, 0)] = 0;

        priority_queue<pair<ll, Coord>> frontier;
        frontier.emplace(0, Coord{0, 0, h_at(0, 0)});

        while (!frontier.empty()) {
            const auto current = frontier.top();
            frontier.pop();

            if (current.second == dest) {
                return costs[r_of(dest)][c_of(dest)][h_of(dest)];
            }

            const int r = r_of(current.second);
            const int c = c_of(current.second);
            const int h = h_of(current.second);

            vector<pair<Coord, ll>> neighs;
            if (h < max_h) {
                neighs.emplace_back(Coord{r, c, h + 1}, costs[r][c][h] + cup);
            }
            if (h > h_at(r, c)) {
                neighs.emplace_back(Coord{r, c, h - 1}, costs[r][c][h] + cdn);
            }
            if (r > 0) {
                neighs.emplace_back(Coord{r - 1, c, h}, costs[r][c][h] + clr);
            }
            if (c > 0) {
                neighs.emplace_back(Coord{r, c - 1, h}, costs[r][c][h] + clr);
            }
            if (r < R - 1) {
                neighs.emplace_back(Coord{r + 1, c, h}, costs[r][c][h] + clr);
            }
            if (c < C - 1) {
                neighs.emplace_back(Coord{r, c + 1, h}, costs[r][c][h] + clr);
            }
        }

        return 2LL * 1e18;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = FlightPlan{}.fly(1, 5, {10, 8, 6, 8, 10}, 40, 10, 20);
        const auto expected = 80;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = FlightPlan{}.fly(6, 1, {10, 8, 16, 18, 8, 12}, 40, 10, 20);
        const auto expected = 480;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = FlightPlan{}.fly(5, 5, { 100, 1000, 100, 100, 100, 97, 9999, 9999, 9999, 100, 93, 9999, 0, 9999, 100, 99, 9999, 83, 65, 100, 98, 93, 90, 9999, 95}, 1000, 1000, 1);
        const auto expected = 5010;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = FlightPlan{}.fly(5, 5, { 100, 1000, 100, 100, 100, 97, 9999, 9999, 9999, 100, 93, 9999, 0, 9999, 100, 99, 9999, 83, 65, 100, 98, 93, 90, 9999, 95}, 1, 1, 1000);
        const auto expected = 9805;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = FlightPlan{}.fly(1, 1, {47}, 123, 234, 345);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
