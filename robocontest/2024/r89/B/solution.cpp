#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static const string Mate{"MOT"};
static const string Draw{"DURRANG"};

static const vector<pii> Deltas{
    {1, 0},   // N
    {1, 1},   // NE
    {0, 1},   // E
    {-1, 1},  // SE
    {-1, 0},  // S
    {-1, -1}, // SW
    {0, -1},  // W
    {1, -1},  // NW
};

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool in_bounds(const int x) { return 0 <= x && x < 8; }

bool in_bounds(const pii roco) {
    return in_bounds(roco.first) && in_bounds(roco.second);
}

pii roco_of(const string &code) {
    assert(sz(code) == 2);
    return {inof(code[1]) - inof('1'), inof(code[0]) - inof('a')};
}

bool are_adjacent(const pii a, const pii b) {
    assert(in_bounds(a) && in_bounds(b) && a != b);
    return max(abs(a.first - b.first), abs(a.second - b.second)) == 1;
}

bool is_beated(const pii xk, const pii yk, const pii yq0) {
    for (const auto &delta : Deltas) {
        auto yq = yq0;
        while (in_bounds(yq + delta) && yq + delta != yk) {
            yq = yq + delta;
            if (yq == xk) return true;
        }
    }
    return false;
}

bool can_move(const pii xk0, const pii yk, const pii yq) {
    for (const auto &delta : Deltas) {
        const auto xk = xk0 + delta;
        if (in_bounds(xk) && xk != yk && xk != yq && !are_adjacent(xk, yk) &&
            !are_adjacent(xk, yq) && !is_beated(xk, yk, yq)) {
            return true;
        }
    }
    return false;
}

bool is_mate(const pii xk, const pii yk, const pii yq) {
    if (are_adjacent(xk, yq)) {
        return are_adjacent(yq, yk) && !can_move(xk, yk, yq);
    } else {
        return is_beated(xk, yk, yq) && !can_move(xk, yk, yq);
    }
}

string outcome(const pii xk, const pii yk, const pii yq0) {
    const auto is_available = [&](const pii yq) {
        return in_bounds(yq) && yq != yk && yq != xk;
    };

    for (const auto &delta : Deltas) {
        auto yq = yq0;
        while (is_available(yq + delta)) {
            yq = yq + delta;
            if (is_mate(xk, yk, yq)) return Mate;
        }
    }
    return Draw;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xk, yk, yq;
    cin >> xk >> yk >> yq;

    cout << outcome(roco_of(xk), roco_of(yk), roco_of(yq)) << '\n';
    return 0;
}
