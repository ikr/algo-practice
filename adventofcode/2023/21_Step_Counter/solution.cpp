#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<int, int>;
using TCoord = pair<int, int>;

static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

using lll = __int128_t;
using ulll = __uint128_t;

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

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    Coord src{-1, -1};
    for (int r = 0; r < sz(grid); ++r) {
        for (int c = 0; c < sz(grid[r]); ++c) {
            if (grid[r][c] == 'S') {
                src = {r, c};
                break;
            }
        }
        if (src.first != -1) break;
    }
    assert(src.first != -1 && src.second != -1);

    const int M = sz(grid);
    assert(sz(grid) == sz(grid[0]));

    const auto inf_grid_at = [&](const Coord p) -> char {
        const auto r = ((p.first % M) + M) % M;
        const auto c = ((p.second % M) + M) % M;
        return grid[r][c];
    };

    const auto adjacent = [&](const Coord p) {
        vector<Coord> ans;
        for (const auto &d : Delta) {
            const auto np = p + d;
            if (inf_grid_at(np) == '#') continue;
            ans.push_back(np);
        }
        return ans;
    };

    set<Coord> gen{src};

    vector<ll> memo(M / 2 + 2 * M + 1, 0);

    const int MaxSteps = sz(memo) - 1;
    for (int step = 1; step <= MaxSteps; ++step) {
        set<Coord> gen_;

        for (const auto &p : gen) {
            for (const auto &np : adjacent(p)) gen_.insert(np);
        }

        swap(gen_, gen);
        memo[step] = sz(gen);
    }

    cerr << memo << endl;

    // Interpolation of a quadratic function
    // https://mathworld.wolfram.com/LagrangeInterpolatingPolynomial.html
    //
    const auto x1 = 0LL;
    const auto y1 = memo[M / 2];

    const auto x2 = 1LL;
    const auto y2 = memo[M / 2 + M];

    const auto x3 = 2LL;
    const auto y3 = memo[M / 2 + 2 * M];

    const auto F = [&](const ll x) -> ll {
        auto A = y1 * (x - x2) * (x - x3);
        assert(A % ((x1 - x2) * (x1 - x3)) == 0LL);
        A /= (x1 - x2) * (x1 - x3);

        auto B = y2 * (x - x1) * (x - x3);
        assert(B % ((x2 - x1) * (x2 - x3)) == 0LL);
        B /= (x2 - x1) * (x2 - x3);

        auto C = y3 * (x - x1) * (x - x2);
        assert(C % ((x3 - x1) * (x3 - x2)) == 0LL);
        C /= (x3 - x1) * (x3 - x2);

        return A + B + C;
    };

    const ll FinalStep = 26501365;
    const auto X = (FinalStep - M / 2) / M;
    cout << F(X) << '\n';

    const lll boo = 3485762934540395;
    cerr << (boo * boo) << endl;
    return 0;
}
