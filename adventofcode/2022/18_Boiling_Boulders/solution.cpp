#include <bits/stdc++.h>
using namespace std;

using Coord = tuple<int, int, int>;

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

int main() {
    set<Coord> scan;
    for (string line; getline(cin, line);) {
        const auto src = split(",", line);
        scan.emplace(stoi(src[0]), stoi(src[1]), stoi(src[2]));
    }

    cout << surface_area(scan) << '\n';
    return 0;
}
