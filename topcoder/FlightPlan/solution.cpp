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

        const auto h_at = [&H, C](const int r, const int c) -> ll {
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
            if (r > 0 && h_at(r - 1, c) <= h) {
                neighs.emplace_back(Coord{r - 1, c, h}, costs[r][c][h] + clr);
            }
            if (c > 0 && h_at(r, c - 1) <= h) {
                neighs.emplace_back(Coord{r, c - 1, h}, costs[r][c][h] + clr);
            }
            if (r < R - 1 && h_at(r + 1, c) <= h) {
                neighs.emplace_back(Coord{r + 1, c, h}, costs[r][c][h] + clr);
            }
            if (c < C - 1 && h_at(r, c + 1) <= h) {
                neighs.emplace_back(Coord{r, c + 1, h}, costs[r][c][h] + clr);
            }

            for (const auto &neigh : neighs) {
                const auto coord = neigh.first;
                const auto new_cost = neigh.second;

                if (costs[r_of(coord)][c_of(coord)][h_of(coord)] == -1 ||
                    new_cost < costs[r_of(coord)][c_of(coord)][h_of(coord)]) {
                    costs[r_of(coord)][c_of(coord)][h_of(coord)] = new_cost;

                    const auto priority =
                        -(new_cost +
                          direct_flight_cost({cup, cdn, clr}, coord, dest));

                    frontier.emplace(priority, coord);
                }
            }
        }

        return 2LL * 1e18;
    }
};

template <typename T> struct RndInt final {
    RndInt(const T lo, const T hi) : m_gen{random_device{}()}, m_dist{lo, hi} {}
    T next() { return m_dist(m_gen); }

  private:
    mt19937 m_gen;
    uniform_int_distribution<T> m_dist;
};

struct Model final {
    vector<vector<int>> histo;
    UnitCosts unit_costs;

    vector<int> linerize_histo() const {
        const int H = histo.size();
        const int W = histo[0].size();

        vector<int> ans(H * W, -1);
        for (int ro = 0; ro < H; ++ro) {
            for (int co = 0; co < W; ++co) {
                ans[ro * W + co] = histo[ro][co];
            }
        }
        return ans;
    }
};

Model random_model() {
    RndInt<int> r_1_50(1, 50);

    const int H = r_1_50.next();
    const int W = r_1_50.next();

    RndInt<int> r_0_10e6(0, 50);
    vector<vector<int>> histo(H, vector<int>(W));

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            histo[ro][co] = r_0_10e6.next();
        }
    }

    RndInt<int> r_1_10e6(1, 50);
    return {histo, {r_1_10e6.next(), r_1_10e6.next(), r_1_10e6.next()}};
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

static const vector<pair<int, int>> DELTAS{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
struct Oracle final {
    int BFS(int R, int C, const vector<int> &H, int h) {
        vector<vector<int>> dist(R, vector<int>(C, -1));
        vector<pair<int, int>> q = {{0, 0}};
        dist[0][0] = 0;

        for (auto i = 0U; i < q.size(); ++i) {
            int r = q[i].first;
            int c = q[i].second;

            for (pair<int, int> delta : DELTAS) {
                int r2 = r + delta.first;
                int c2 = c + delta.second;
                if (r2 >= 0 && c2 >= 0 && r2 < R && c2 < C &&
                    H[C * r2 + c2] <= h && dist[r2][c2] == -1) {
                    dist[r2][c2] = dist[r][c] + 1;
                    q.push_back({r2, c2});
                }
            }
        }

        return dist[R - 1][C - 1];
    }

    long long fly(int R, int C, vector<int> H, int cup, int cdn, int clr) {
        long long min_cost = -1;

        for (int h : H) {
            if (h < H[0] || h < H.back()) continue;

            int bfs_cost = BFS(R, C, H, h);

            if (bfs_cost < 0) continue;

            long long cost = bfs_cost * (long long)clr +
                             (h - H[0]) * (long long)cup +
                             (h - H.back()) * (long long)cdn;
            if (min_cost < 0)
                min_cost = cost;
            else
                min_cost = min(min_cost, cost);
        }

        return min_cost;
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

        const auto control = Oracle{}.fly(5, 5, { 100, 1000, 100, 100, 100, 97, 9999, 9999, 9999, 100, 93, 9999, 0, 9999, 100, 99, 9999, 83, 65, 100, 98, 93, 90, 9999, 95}, 1, 1, 1000);
        EXPECT(control == expected);
    },
    CASE("Example 4") {
        const auto actual = FlightPlan{}.fly(1, 1, {47}, 123, 234, 345);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("20 random models") {
        for (int i = 0; i < 20; ++i) {
            const auto m = random_model();
            const auto actual = FlightPlan{}.fly(m.histo.size(),
                                                 m.histo[0].size(),
                                                 m.linerize_histo(),
                                                 m.unit_costs.cup, m.unit_costs.cdn, m.unit_costs.clr);
            const auto expected = Oracle{}.fly(m.histo.size(),
                                               m.histo[0].size(),
                                               m.linerize_histo(),
                                               m.unit_costs.cup, m.unit_costs.cdn, m.unit_costs.clr);
            if (actual != expected) {
                cout << "R:" << m.histo.size() << " C:" << m.histo[0].size() << " " << m.linerize_histo() << ' ';
                cout << "cup:" << m.unit_costs.cup << " cdn:" << m.unit_costs.cdn <<  " clr:" << m.unit_costs.clr << '\n';
            }
            EXPECT(actual == expected);
        }
    },
    CASE("Pyramid with blocks") {
        Model m{{
                {0, 0, 0, 0, 0, 0, 9},
                {0, 1, 1, 1, 1, 1, 0},
                {0, 1, 2, 2, 2, 1, 0},
                {0, 1, 2, 3, 2, 1, 0},
                {0, 1, 2, 2, 2, 1, 0},
                {0, 1, 1, 1, 1, 2, 9},
                {9, 0, 0, 0, 0, 9, 0},
            }, UnitCosts{1, 1, 3}};
        const auto actual = FlightPlan{}.fly(m.histo.size(),
                                             m.histo[0].size(),
                                             m.linerize_histo(),
                                             m.unit_costs.cup, m.unit_costs.cdn, m.unit_costs.clr);
        const auto expected = Oracle{}.fly(m.histo.size(),
                                           m.histo[0].size(),
                                           m.linerize_histo(),
                                           m.unit_costs.cup, m.unit_costs.cdn, m.unit_costs.clr);
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
