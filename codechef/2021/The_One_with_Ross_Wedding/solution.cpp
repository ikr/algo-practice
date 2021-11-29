#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = complex<int>;
constexpr int X(const Coord coord) { return coord.real(); }
constexpr int Y(const Coord coord) { return coord.imag(); }

enum class Axis { X, Y };

bool can_reach(const string &p, const Coord dest, const Axis initial_axis) {
    Coord curr{0, 0};
    Axis ax = initial_axis;

    for (const char instr : p) {
        if (instr == '1') {
            if (ax == Axis::X) {
                if (X(curr) <= X(dest)) {
                    curr = Coord(X(curr) + 1, Y(curr));
                } else {
                    curr = Coord(X(curr) - 1, Y(curr));
                }
            } else {
                if (Y(curr) <= Y(dest)) {
                    curr = Coord(X(curr), Y(curr) + 1);
                } else {
                    curr = Coord(X(curr), Y(curr) - 1);
                }
            }
        } else {
            assert(instr == '0');

            if (ax == Axis::X) {
                if (Y(curr) <= Y(dest)) {
                    curr = Coord(X(curr), Y(curr) + 1);
                } else {
                    curr = Coord(X(curr), Y(curr) - 1);
                }

                ax = Axis::Y;
            } else {
                if (X(curr) <= X(dest)) {
                    curr = Coord(X(curr) + 1, Y(curr));
                } else {
                    curr = Coord(X(curr) - 1, Y(curr));
                }

                ax = Axis::X;
            }
        }
    }

    return curr == dest;
}

bool can_reach(const string &p, const Coord dest) {
    return can_reach(p, dest, Axis::X) || can_reach(p, dest, Axis::Y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;

        string p(n, ' ');
        cin >> p;

        cout << (can_reach(p, {x, y}) ? "YES" : "NO") << '\n';
    }

    return 0;
}
