#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Intvl = pair<int, int>;

constexpr int COORD_MAX = 4000000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int manhattan(const Coord a, const Coord b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

constexpr int intvl_size(const Intvl ab) { return ab.second - ab.first + 1; }

constexpr bool intersect(const Intvl ab, const Intvl cd) {
    return !(ab.second < cd.first || cd.second < ab.first);
}

constexpr Intvl union_of(const Intvl ab, const Intvl cd) {
    array<int, 4> abcd{ab.first, ab.second, cd.first, cd.second};
    sort(begin(abcd), end(abcd));
    return {abcd[0], abcd.back()};
}

vector<Intvl>
excluded_positions_at_y0(const vector<pair<Coord, Coord>> &tathers,
                         const int y0) {
    vector<Intvl> result;

    const auto new_intvl = [&](Intvl ab) -> void {
        for (auto it = cbegin(result); it != cend(result);) {
            if (intersect(ab, *it)) {
                ab = union_of(ab, *it);
                it = result.erase(it);
            } else {
                ++it;
            }
        }

        result.push_back(ab);
        sort(begin(result), end(result));
    };

    for (const auto &[sensor, beacon] : tathers) {
        const auto r = manhattan(sensor, beacon);
        const auto [sx, sy] = sensor;
        const auto d = abs(sy - y0);
        if (d > r) continue;

        const auto a = sx - (r - d);
        const auto b = sx + (r - d);
        new_intvl({a, b});
    }

    sort(begin(result), end(result));
    return result;
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

int main() {
    const regex pattern{"^Sensor at x=(-?[0-9]+), y=(-?[0-9]+): closest beacon "
                        "is at x=(-?[0-9]+), y=(-?[0-9]+)$"};

    vector<pair<Coord, Coord>> tathers;

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);

        const auto sx = stoi(m[1].str());
        const auto sy = stoi(m[2].str());
        const auto bx = stoi(m[3].str());
        const auto by = stoi(m[4].str());

        tathers.emplace_back(Coord{sx, sy}, Coord{bx, by});
    }

    const auto [x0, y0] = [&]() -> Coord {
        for (int y = 0; y <= COORD_MAX; ++y) {
            const auto excl = excluded_positions_at_y0(tathers, y);

            for (int i = 1; i < sz(excl); ++i) {
                const auto mb_x = excl[i].first - 1;

                if (excl[i - 1].second + 2 == excl[i].first && 0 <= mb_x &&
                    mb_x <= COORD_MAX) {
                    return {mb_x, y};
                }
            }
        }

        return {-1, -1};
    }();

    cout << (4000000LL * x0 + y0) << '\n';
    return 0;
}
