#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// Geometry lib source:
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

template <class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

typedef Point<double> P;
double segDist(P &s, P &e, P &p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}

#define rep(i, a, b) for (int i = a; i < (b); ++i)

static constexpr double EPS = 0.000001;

template <class P> bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i, 0, n) {
        P q = p[(i + 1) % n];
        // if (onSegment(p[i], q, a)) return !strict;
        if (segDist(p[i], q, a) < EPS) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}

static constexpr double INF = 1e10;

constexpr double sqr(const double x) { return x * x; }

double dist(const P &a, const P &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double perimeter(const P &a, const P &b, const P &c) {
    return dist(a, b) + dist(b, c) + dist(a, c);
}

bool is_degenerate(const P &a, const P &b, const P &c) {
    P aa{a};
    P bb{b};
    P cc{c};
    return segDist(aa, bb, cc) < EPS;
}

optional<double> solve_brute(const vector<P> &ps, const P &B) {
    double best = INF;

    for (int i = 0; i < sz(ps) - 2; ++i) {
        for (int j = i + 1; j < sz(ps) - 1; ++j) {
            for (int k = j + 1; k < sz(ps); ++k) {
                const auto a = ps[i];
                const auto b = ps[j];
                const auto c = ps[k];

                vector tri{a, b, c};
                if (is_degenerate(a, b, c) || !inPolygon(tri, B)) continue;

                best = min(best, perimeter(a, b, c));
            }
        }
    }

    return best >= INF ? nullopt : optional{best};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<P> ps(N);
        for (auto &p : ps) {
            cin >> p.x >> p.y;
        }

        P B;
        cin >> B.x >> B.y;

        const auto ans = solve_brute(ps, B);

        cout << "Case #" << i << ": ";
        if (ans) {
            cout << *ans;
        } else {
            cout << "IMPOSSIBLE";
        }
        cout << '\n';
    }

    return 0;
}
