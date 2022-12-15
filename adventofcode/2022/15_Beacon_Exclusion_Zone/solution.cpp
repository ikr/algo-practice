#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Intvl = pair<int, int>;

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

int excluded_positions_num_at_y0(const vector<pair<Coord, Coord>> &tathers,
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

    for (const auto &[_, beacon] : tathers) {
        const auto [bx, by] = beacon;
        if (by != y0) continue;

        for (auto it = cbegin(result); it != cend(result); ++it) {
            const auto [c, d] = *it;
            if (bx < c || d < bx) continue;

            it = result.erase(it);
            if (bx == c) {
                if (c != d) result.emplace_back(c + 1, d);
            } else if (bx == d) {
                result.emplace_back(c, d - 1);
            } else {
                assert(c < bx && bx < d);
                result.emplace_back(c, bx - 1);
                result.emplace_back(bx + 1, d);
            }
            break;
        }
        break;
    }

    return transform_reduce(cbegin(result), cend(result), 0, plus<int>{},
                            intvl_size);
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

    cout << excluded_positions_num_at_y0(tathers, 2000000) << '\n';
    return 0;
}
