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
    return 0;
}
