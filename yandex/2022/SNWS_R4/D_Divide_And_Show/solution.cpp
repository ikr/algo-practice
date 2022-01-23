#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// Source:
// https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry

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

template <class P> int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template <class P> int sideOf(const P &s, const P &e, const P &p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}

using Seg = pair<Point<ll>, Point<ll>>;

bool first_cut_part_intact(const vector<Seg> &cuts) {
    if (sz(cuts) < 2) return true;
    const auto [A, B] = cuts[0];

    set<int> signs;
    for (int i = 1; i < sz(cuts); ++i) {
        const auto [C, D] = cuts[i];
        signs.insert(sideOf(A, B, C));
        signs.insert(sideOf(A, B, D));
    }

    return sz(signs) < 3;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Seg> cuts(k);
    for (auto &seg : cuts) {
        auto &[A, B] = seg;
        cin >> A.x >> A.y >> B.x >> B.y;
    }

    cout << (first_cut_part_intact(cuts) ? "YES" : "NO") << '\n';
    return 0;
}
