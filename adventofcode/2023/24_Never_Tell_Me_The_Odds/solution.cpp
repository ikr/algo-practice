#include "z3++.h"
#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

using Coord = array<ll, 3>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

Coord parse_coord(const string &s) {
    const auto token = split(", ", s);
    return {stoll(token[0]), stoll(token[1]), stoll(token[2])};
}

void smt_solve(const Coord &p1, const Coord &v1, const Coord &p2,
               const Coord &v2, const Coord &p3, const Coord &v3) {
    z3::config cfg;
    cfg.set("auto_config", true);
    z3::context c(cfg);

    // Input data values
    auto p1x = c.int_val(p1[0]);
    auto p1y = c.int_val(p1[1]);
    auto p1z = c.int_val(p1[2]);
    auto v1x = c.int_val(v1[0]);
    auto v1y = c.int_val(v1[1]);
    auto v1z = c.int_val(v1[2]);

    auto p2x = c.int_val(p2[0]);
    auto p2y = c.int_val(p2[1]);
    auto p2z = c.int_val(p2[2]);
    auto v2x = c.int_val(v2[0]);
    auto v2y = c.int_val(v2[1]);
    auto v2z = c.int_val(v2[2]);

    auto p3x = c.int_val(p3[0]);
    auto p3y = c.int_val(p3[1]);
    auto p3z = c.int_val(p3[2]);
    auto v3x = c.int_val(v3[0]);
    auto v3y = c.int_val(v3[1]);
    auto v3z = c.int_val(v3[2]);

    // Unknowns
    z3::expr p0x = c.int_const("p0x");
    z3::expr p0y = c.int_const("p0y");
    z3::expr p0z = c.int_const("p0z");

    z3::expr v0x = c.int_const("v0x");
    z3::expr v0y = c.int_const("v0y");
    z3::expr v0z = c.int_const("v0z");

    z3::expr t1 = c.int_const("t1");
    z3::expr t2 = c.int_const("t2");
    z3::expr t3 = c.int_const("t3");

    z3::solver s(c);
    // p0 + t1 * v0 = p1 + t1 * v1
    s.add(p0x + t1 * v0x == p1x + t1 * v1x);
    s.add(p0y + t1 * v0y == p1y + t1 * v1y);
    s.add(p0z + t1 * v0z == p1z + t1 * v1z);

    // p1 + t1 * v1 + t2 * v0 = p2 + (t1 + t2) * v2
    s.add(p1x + t1 * v1x + t2 * v0x == p2x + (t1 + t2) * v2x);
    s.add(p1y + t1 * v1y + t2 * v0y == p2y + (t1 + t2) * v2y);
    s.add(p1z + t1 * v1z + t2 * v0z == p2z + (t1 + t2) * v2z);

    // p2 + (t1 + t2) * v2 + t3 * v0 = p3 + (t1 + t2 + t3) * v3
    s.add(p2x + (t1 + t2) * v2x + t3 * v0x == p3x + (t1 + t2 + t3) * v3x);
    s.add(p2y + (t1 + t2) * v2y + t3 * v0y == p3y + (t1 + t2 + t3) * v3y);
    s.add(p2z + (t1 + t2) * v2z + t3 * v0z == p3z + (t1 + t2 + t3) * v3z);

    s.add(t1 >= 0);
    s.add(t2 >= 0);
    s.add(t3 >= 0);

    if (s.check() != z3::sat) return;
    auto m = s.get_model();
    cout << m << "\n\n";
}

int main() {
    vector<Coord> initial_locations;
    vector<Coord> velocities;

    for (string line; getline(cin, line);) {
        const auto parts = split(" @ ", line);
        initial_locations.push_back(parse_coord(parts[0]));
        velocities.push_back(parse_coord(parts[1]));
    }

    const auto n = sz(initial_locations);
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                array indices{i, j, k};
                do {
                    const auto p1 = initial_locations[indices[0]];
                    const auto v1 = velocities[indices[0]];

                    const auto p2 = initial_locations[indices[1]];
                    const auto v2 = velocities[indices[1]];

                    const auto p3 = initial_locations[indices[2]];
                    const auto v3 = velocities[indices[2]];

                    smt_solve(p1, v1, p2, v2, p3, v3);
                } while (next_permutation(begin(indices), end(indices)));
            }
        }
    }

    return 0;
}
