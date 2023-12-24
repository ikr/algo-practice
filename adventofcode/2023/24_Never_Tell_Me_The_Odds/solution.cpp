#include <bits/stdc++.h>
using namespace std;

using lll = __int128_t;
using ulll = __uint128_t;
using Coord = tuple<lll, lll, lll>;

ostream &operator<<(ostream &dest, const lll value) {
    ostream::sentry s(dest);
    if (s) {
        ulll tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);

        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);

        if (value < 0) {
            --d;
            *d = '-';
        }

        const int len = static_cast<int>(end(buffer) - d);
        if (dest.rdbuf()->sputn(d, len) != len) dest.setstate(ios_base::badbit);
    }
    return dest;
}

constexpr lll X(const Coord &p) { return get<0>(p); }
constexpr lll Y(const Coord &p) { return get<1>(p); }
constexpr lll Z(const Coord &p) { return get<2>(p); }

ostream &operator<<(ostream &os, const Coord &p) {
    os << '(' << X(p) << ' ' << Y(p) << ' ' << Z(p) << ')';
    return os;
}

constexpr Coord operator+(const Coord &a, const Coord &b) {
    return {X(a) + X(b), Y(a) + Y(b), Z(a) + Z(b)};
}

constexpr Coord scaled_by(const Coord &a, const lll k) {
    return {X(a) * k, Y(a) * k, Z(a) * k};
};

constexpr lll sqr(const lll a) { return a * a; }

constexpr lll dist2(const Coord &a, const Coord &b) {
    return sqr(X(a) - X(b)) + sqr(Y(a) - Y(b)) + sqr(Z(a) - Z(b));
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

    cerr << initial_locations << endl;
    cerr << velocities << endl;

    return 0;
}
