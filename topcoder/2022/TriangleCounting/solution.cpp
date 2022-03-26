#include "lest.hpp"
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

// SRC:
// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
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

template <class P> double lineDist(const P &a, const P &b, const P &p) {
    return (double)(b - a).cross(p - a) / (b - a).dist();
}

using Pt = Point<long long>;

struct TriangleCounting final {
    int count(const vector<int> &xs, const vector<int> &ys) const {
        int result{};

        for (int i = 0; i < sz(xs) - 2; ++i) {
            for (int j = i + 1; j < sz(xs) - 1; ++j) {
                for (int k = j + 1; k < sz(xs); ++k) {
                    Pt p1(xs[i], ys[i]);
                    Pt p2(xs[j], ys[j]);
                    Pt p3(xs[k], ys[k]);

                    if (p1 == p2 || p1 == p3 || p2 == p3) continue;
                    if (lineDist(p1, p2, p3)) ++result;
                }
            }
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TriangleCounting{}.count({ 0, 2, 4 }, { 0, 5, 3 });
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TriangleCounting{}.count({ 0, 2, 4, 6 }, { 0, 5, 3, 15 });
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = TriangleCounting{}.count({ 0, 0, 1}, { 0, 0, 1});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
