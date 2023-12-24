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

using Matrix = vector<vector<lll>>;

Matrix pairwise_dist2(const vector<Coord> &ps) {
    const auto n = sz(ps);
    Matrix result(n, vector<lll>(n, 0));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            result[i][j] = dist2(ps[i], ps[j]);
            result[j][i] = result[i][j];
        }
    }
    return result;
}

void min_special(Matrix &a, const Matrix &b, Matrix &T, const lll t) {
    const auto n = sz(a);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (b[i][j] < a[i][j]) {
                a[i][j] = b[i][j];
                T[i][j] = t;
            }

            a[j][i] = a[i][j];
            T[j][i] = T[i][j];
        }
    }
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

    const auto locations_at_time = [&](const lll t) -> vector<Coord> {
        vector<Coord> result(n);
        ranges::transform(initial_locations, velocities, begin(result),
                          [&](const Coord &p0, const Coord &v) -> Coord {
                              return p0 + scaled_by(v, t);
                          });
        return result;
    };

    cerr << "Distances @ 0:\n" << pairwise_dist2(initial_locations) << endl;

    Matrix min_dist2 = pairwise_dist2(initial_locations);
    Matrix min_dist2_t(n, vector<lll>(n, 0));

    for (lll t = 1; t <= 8; ++t) {
        cerr << "Distances @ " << t << ":\n"
             << pairwise_dist2(locations_at_time(t)) << endl;

        min_special(min_dist2, pairwise_dist2(locations_at_time(t)),
                    min_dist2_t, t);
    }

    cerr << min_dist2 << endl;
    cerr << min_dist2_t << endl;
    return 0;
}
