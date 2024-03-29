#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
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

template <class T> T polygonArea2(vector<Point<T>> &v) {
    T a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}

bool is_degenerate(const P &a, const P &b, const P &c) {
    vector pl{a, b, c};
    return abs(polygonArea2(pl)) / 2.0 < EPS;
}

using Tri = tuple<int, int, int>;

map<pii, vector<Tri>> gather_tris_by_side(const vector<P> &ps) {
    map<pii, vector<Tri>> ans;

    for (int i = 0; i < sz(ps) - 2; ++i) {
        for (int j = i + 1; j < sz(ps) - 1; ++j) {
            for (int k = j + 1; k < sz(ps); ++k) {
                if (is_degenerate(ps[i], ps[j], ps[k])) continue;

                ans[{i, j}].emplace_back(i, j, k);
                ans[{j, k}].emplace_back(i, j, k);
                ans[{i, k}].emplace_back(i, j, k);
            }
        }
    }

    return ans;
}

double seg_dist(const P &s, const P &e, const P &p) {
    P ss{s};
    P ee{e};
    P pp{p};
    return segDist(ss, ee, pp);
}

template <class P> int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

pii two_tops(const pii uv, const Tri ijk, const Tri pqr) {
    const auto [u, v] = uv;

    pii ans{-1, -1};

    {
        const auto [i, j, k] = ijk;
        if (i != u && i != v) {
            ans.first = i;
        } else if (j != u && j != v) {
            ans.first = j;
        } else if (k != u && k != v) {
            ans.first = k;
        }
    }

    {
        const auto [p, q, r] = pqr;
        if (p != u && p != v) {
            ans.second = p;
        } else if (q != u && q != v) {
            ans.second = q;
        } else if (r != u && r != v) {
            ans.second = r;
        }
    }

    return ans;
}

optional<double> solve_brute(const vector<P> &ps, const P &B) {
    const auto tris_by_side = gather_tris_by_side(ps);

    double best = INF;

    for (int i = 0; i < sz(ps) - 2; ++i) {
        for (int j = i + 1; j < sz(ps) - 1; ++j) {
            for (int k = j + 1; k < sz(ps); ++k) {
                if (is_degenerate(ps[i], ps[j], ps[k])) continue;

                vector<P> pl{ps[i], ps[j], ps[k]};
                if (inPolygon(pl, B)) {
                    best = min(best, perimeter(ps[i], ps[j], ps[k]));
                    continue;
                }

                for (const auto [u, v] : vector<pii>{{i, j}, {j, k}, {i, k}}) {
                    if (seg_dist(ps[u], ps[v], B) < EPS) {
                        for (const auto [p, q, r] : tris_by_side.at({u, v})) {
                            if (Tri{i, j, k} == Tri{p, q, r} ||
                                is_degenerate(ps[p], ps[q], ps[r])) {
                                continue;
                            }

                            const auto [t1, t2] =
                                two_tops({u, v}, {i, j, k}, {p, q, r});
                            if (sideOf(ps[u], ps[v], ps[t1]) ==
                                sideOf(ps[u], ps[v], ps[t2])) {
                                continue;
                            }

                            const auto candidate =
                                perimeter(ps[i], ps[j], ps[k]) +
                                perimeter(ps[p], ps[q], ps[r]) -
                                2.0 * dist(ps[u], ps[v]);

                            best = min(best, candidate);
                        }
                    }
                }
            }
        }
    }

    return best >= INF ? nullopt : optional{best};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

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
