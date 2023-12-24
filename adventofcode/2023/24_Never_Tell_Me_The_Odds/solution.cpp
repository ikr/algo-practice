#include <bits/stdc++.h>
using namespace std;

namespace kactl {
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template <class P> pair<int, P> line_inter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}
} // namespace kactl

using Point2D = kactl::Point<long double>;
using ll = long long;
using Coord = tuple<ll, ll, ll>;

// static constexpr long double TestAreaLo = 7;
// static constexpr long double TestAreaHi = 27;

static constexpr long double TestAreaLo = 200000000000000.0;
static constexpr long double TestAreaHi = 400000000000000.0;

constexpr bool is_within_test_area(const long double a) {
    return TestAreaLo <= a && a <= TestAreaHi;
}

constexpr bool is_within_test_area(const Point2D &p) {
    return is_within_test_area(p.x) && is_within_test_area(p.y);
}

const bool are_codirected(const Point2D &v1, const Point2D &v2) {
    return v1.dot(v2) > 0.0;
}

constexpr ll X(const Coord &p) { return get<0>(p); }
constexpr ll Y(const Coord &p) { return get<1>(p); }
constexpr ll Z(const Coord &p) { return get<2>(p); }

ostream &operator<<(ostream &os, const Coord &p) {
    os << '(' << X(p) << ' ' << Y(p) << ' ' << Z(p) << ')';
    return os;
}

constexpr Coord operator+(const Coord &a, const Coord &b) {
    return {X(a) + X(b), Y(a) + Y(b), Z(a) + Z(b)};
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
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

    int pairwise_intersections_count{};
    for (int i = 0; i < sz(initial_locations) - 1; ++i) {
        for (int j = i + 1; j < sz(initial_locations); ++j) {
            const auto s1 =
                Point2D(X(initial_locations[i]), Y(initial_locations[i]));
            const auto v1 = Point2D(X(velocities[i]), Y(velocities[i]));

            const auto s2 =
                Point2D(X(initial_locations[j]), Y(initial_locations[j]));
            const auto v2 = Point2D(X(velocities[j]), Y(velocities[j]));

            const auto [outcome, p] =
                kactl::line_inter(s1, s1 + v1, s2, s2 + v2);

            cerr << "i:" << i << " j:" << j << " outcome:" << outcome
                 << " p:" << p << endl;

            if (outcome != 0 && is_within_test_area(p) &&
                are_codirected(p - s1, v1) && are_codirected(p - s2, v2)) {
                ++pairwise_intersections_count;
            }
        }
    }
    cout << pairwise_intersections_count << '\n';
    return 0;
}
