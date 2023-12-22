#include <bits/stdc++.h>
using namespace std;

using Point = tuple<int, int, int>;
using Brick = vector<Point>;

template <typename T>
ostream &operator<<(ostream &os, const tuple<T, T, T> &p) {
    const auto [x, y, z] = p;
    os << '(' << x << ' ' << y << ' ' << z << ')';
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

constexpr int X(const Point &p) { return get<0>(p); }
constexpr int Y(const Point &p) { return get<1>(p); }
constexpr int Z(const Point &p) { return get<2>(p); }

Point parse_point(const string &s) {
    const auto tokens = split(",", s);
    assert(sz(tokens) == 3);
    return {stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2])};
}

vector<Point> all_voxels(const Point &pa, const Point &pb) {
    const auto [xa, ya, za] = pa;
    const auto [xb, yb, zb] = pb;
    vector<Point> result;
    for (int x = xa; x <= xb; ++x) {
        for (int y = ya; y <= yb; ++y) {
            for (int z = za; z <= zb; ++z) result.emplace_back(x, y, z);
        }
    }
    return result;
}

constexpr tuple<int, int, int> zxy(const Point &p) {
    return {Z(p), X(p), Y(p)};
}

constexpr bool cmp_by_z(const Point &p, const Point &q) {
    return zxy(p) < zxy(q);
}

bool can_shift_down(const set<Point> &voxels, const Brick &b) {
    set<Point> own_voxels(cbegin(b), cend(b));

    for (const auto &p : b) {
        const auto [x, y, z] = p;
        if (z == 1) return false;
        if (own_voxels.contains({x, y, z - 1})) continue;
        if (voxels.contains({x, y, z - 1})) return false;
    }
    return true;
};

bool can_remove(const vector<Brick> &bricks, set<Point> &voxels,
                const int ibrick) {
    const auto b0 = bricks[ibrick];
    for (const auto &p : b0) voxels.erase(p);

    for (int i = 0; i < sz(bricks); ++i) {
        if (i == ibrick) continue;
        if (can_shift_down(voxels, bricks[i])) {
            for (const auto &p : b0) voxels.insert(p);
            return false;
        }
    }

    for (const auto &p : b0) voxels.insert(p);
    return true;
}

int main() {
    vector<Brick> bricks;
    set<Point> voxels;

    for (string line; getline(cin, line);) {
        const auto parts = split("~", line);
        assert(sz(parts) == 2);

        const auto pa = parse_point(parts[0]);
        const auto pb = parse_point(parts[1]);
        const auto vs = all_voxels(pa, pb);
        bricks.push_back(vs);
        voxels.insert(cbegin(vs), cend(vs));
    }

    const auto sort_by_z = [&]() -> void {
        ranges::sort(bricks, [](Brick a, Brick b) {
            ranges::sort(a, cmp_by_z);
            ranges::sort(b, cmp_by_z);
            return zxy(a.front()) < zxy(b.front());
        });
    };

    sort_by_z();

    const auto shift_down = [&](Brick &b) {
        for (auto &p : b) {
            voxels.erase(p);
            const auto [x, y, z] = p;
            p = Point{x, y, z - 1};
            voxels.insert(p);
        }
    };

    const auto shift_one_return_shifted = [&]() -> bool {
        for (auto &b : bricks) {
            if (can_shift_down(voxels, b)) {
                shift_down(b);
                return true;
            }
        }
        return false;
    };

    for (;;) {
        if (!shift_one_return_shifted()) break;
        // sort_by_z();
    }

    int result{};
    for (int i = sz(bricks) - 1; i >= 0; --i) {
        if (can_remove(bricks, voxels, i)) ++result;
    }
    cout << result << '\n';
    return 0;
}
