#include <bits/stdc++.h>
using namespace std;

using Coord = tuple<int, int, int>;

constexpr int SCALAR_MAX = 20;
constexpr int VOLUME_MAX = 2000;

constexpr int X(const Coord &a) { return get<0>(a); }
constexpr int Y(const Coord &a) { return get<1>(a); }
constexpr int Z(const Coord &a) { return get<2>(a); }

constexpr Coord operator+(const Coord &a, const Coord &b) {
    return {X(a) + X(b), Y(a) + Y(b), Z(a) + Z(b)};
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

vector<Coord> adjacent(const Coord &a) {
    return {a + Coord{1, 0, 0},  a + Coord{-1, 0, 0}, a + Coord{0, 1, 0},
            a + Coord{0, -1, 0}, a + Coord{0, 0, 1},  a + Coord{0, 0, -1}};
}

int surface_area(const set<Coord> &scan) {
    int result{};

    for (const auto &a : scan) {
        result += 6;
        for (const auto &b : adjacent(a)) {
            if (scan.contains(b)) --result;
        }
    }

    return result;
}

constexpr bool is_for_sure_in_outer_space(const Coord &a) {
    return X(a) < 0 || X(a) > SCALAR_MAX || Y(a) < 0 || Y(a) > SCALAR_MAX ||
           Z(a) < 0 || Z(a) > SCALAR_MAX;
}

ostream &operator<<(ostream &os, const Coord &a) {
    os << '(' << X(a) << ' ' << Y(a) << ' ' << Z(a) << ')';
    return os;
}

optional<set<Coord>> inner_space(const set<Coord> &scan, const Coord &sprout) {
    assert(!scan.contains(sprout));
    set<Coord> result{sprout};

    const auto recur = [&](const auto self, const Coord u) -> void {
        if (sz(result) > VOLUME_MAX || is_for_sure_in_outer_space(u)) return;
        for (const auto &v : adjacent(u)) {
            if (result.contains(v) || scan.contains(v)) continue;
            result.insert(v);
            self(self, v);
        }
    };

    recur(recur, sprout);

    if (sz(result) > VOLUME_MAX ||
        any_of(cbegin(result), cend(result), is_for_sure_in_outer_space)) {
        return nullopt;
    }
    return result;
}

int outer_surface_area(const set<Coord> &scan) {
    vector<set<Coord>> inner_spaces;

    for (const auto &u : scan) {
        for (const auto &v : adjacent(u)) {
            if (scan.contains(v) ||
                any_of(cbegin(inner_spaces), cend(inner_spaces),
                       [v](const auto &sp) { return sp.contains(v); })) {
                continue;
            }

            const auto isp = inner_space(scan, v);
            if (isp) inner_spaces.push_back(*isp);
        }
    }

    int result = surface_area(scan);
    for (const auto &isp : inner_spaces) {
        result -= surface_area(isp);
    }
    return result;
}

int main() {
    set<Coord> scan;
    for (string line; getline(cin, line);) {
        const auto src = split(",", line);
        scan.emplace(stoi(src[0]), stoi(src[1]), stoi(src[2]));
    }

    cout << outer_surface_area(scan) << '\n';
    return 0;
}
