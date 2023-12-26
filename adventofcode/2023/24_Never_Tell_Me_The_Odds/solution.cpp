#include "z3++.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

    std::cout << "nonlinear example 1\n";
    z3::config cfg;
    cfg.set("auto_config", true);
    z3::context c(cfg);

    z3::expr x = c.real_const("x");
    z3::expr y = c.real_const("y");
    z3::expr z = c.real_const("z");

    z3::solver s(c);

    s.add(x * x + y * y == 1);                        // x^2 + y^2 == 1
    s.add(x * x * x + z * z * z < c.real_val("1/2")); // x^3 + z^3 < 1/2
    s.add(z != 0);
    std::cout << s.check() << "\n";
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
