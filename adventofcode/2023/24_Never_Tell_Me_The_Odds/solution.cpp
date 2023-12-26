#include "z3++.h"
#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

using Coord = array<ll, 3>;

ostream &operator<<(ostream &os, const Coord &p) {
    os << '(' << p[0] << ' ' << p[1] << ' ' << p[2] << ')';
    return os;
}

template <typename T> constexpr T operator+(T a, const T &b) {
    assert(a.size() == b.size());
    ranges::transform(a, b, begin(a),
                      [](const auto x, const auto y) { return x + y; });
    return a;
}

constexpr Coord scaled_by(Coord p, const ll k) {
    ranges::transform(p, begin(p), [k](const auto a) { return a * k; });
    return p;
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

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

int main() {
    vector<Coord> initial_locations;
    vector<Coord> velocities;

    for (string line; getline(cin, line);) {
        const auto parts = split(" @ ", line);
        initial_locations.push_back(parse_coord(parts[0]));
        velocities.push_back(parse_coord(parts[1]));
    }
    cerr << initial_locations << '\n' << velocities << endl;

    z3::config cfg;
    cfg.set("auto_config", true);
    z3::context c(cfg);

    // Input data values
    auto p1x = c.real_val(initial_locations[0][0]);
    auto p1y = c.real_val(initial_locations[0][1]);
    auto p1z = c.real_val(initial_locations[0][2]);
    auto v1x = c.real_val(velocities[0][0]);
    auto v1y = c.real_val(velocities[0][1]);
    auto v1z = c.real_val(velocities[0][2]);

    auto p2x = c.real_val(initial_locations[1][0]);
    auto p2y = c.real_val(initial_locations[1][1]);
    auto p2z = c.real_val(initial_locations[1][2]);
    auto v2x = c.real_val(velocities[1][0]);
    auto v2y = c.real_val(velocities[1][1]);
    auto v2z = c.real_val(velocities[1][2]);

    auto p3x = c.real_val(initial_locations[2][0]);
    auto p3y = c.real_val(initial_locations[2][1]);
    auto p3z = c.real_val(initial_locations[2][2]);
    auto v3x = c.real_val(velocities[2][0]);
    auto v3y = c.real_val(velocities[2][1]);
    auto v3z = c.real_val(velocities[2][2]);

    // Unknowns
    z3::expr p0x = c.real_const("p0x");
    z3::expr p0y = c.real_const("p0y");
    z3::expr p0z = c.real_const("p0z");

    z3::expr v0x = c.real_const("v0x");
    z3::expr v0y = c.real_const("v0y");
    z3::expr v0z = c.real_const("v0z");

    z3::expr t1 = c.real_const("t1");
    z3::expr t2 = c.real_const("t2");
    z3::expr t3 = c.real_const("t3");

    z3::solver s(c);
    // p0 + t1 * v0 = p1 + t1 * v1
    s.add(p0x + t1 * v0x == p1x + t1 * v1x);
    s.add(p0y + t1 * v0y == p1y + t1 * v1y);
    s.add(p0z + t1 * v0z == p1z + t1 * v1z);

    // p1 + t1 * v1 + t2 * v0 = p2 + t2 * v2
    s.add(p1x + t1 * v1x + t2 * v0x == p2x + t2 * v2x);
    s.add(p1y + t1 * v1y + t2 * v0y == p2y + t2 * v2y);
    s.add(p1z + t1 * v1z + t2 * v0z == p2z + t2 * v2z);

    // p2 + t2 * v2 + t3 * v0 = p3 + t3 * v3
    s.add(p2x + t2 * v2x + t3 * v0x == p3x + t3 * v3x);
    s.add(p2y + t2 * v2y + t3 * v0y == p3y + t3 * v3y);
    s.add(p2z + t2 * v2z + t3 * v0z == p3z + t3 * v3z);

    s.add(t1 > 0);
    s.add(t2 > 0);
    s.add(t3 > 0);

    std::cout << "check:" << s.check() << "\n";
    z3::model m = s.get_model();
    std::cout << m << "\n";
    z3::set_param("pp.decimal", true); // set decimal notation
    std::cout << "model in decimal notation\n";
    std::cout << m << "\n";
    z3::set_param("pp.decimal-precision",
                  50); // increase number of decimal places to 50.
    std::cout << "model using 50 decimal places\n";
    std::cout << m << "\n";
    z3::set_param("pp.decimal", false); // disable decimal notation

    return 0;
}
