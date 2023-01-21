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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using Coord = array<int, 3>;

struct State final {
    vector<Coord> pos;
    vector<Coord> vel;
};

ostream &operator<<(ostream &os, const State &state) {
    for (int i = 0; i < sz(state.pos); ++i) {
        os << "pos=" << state.pos << " vel=" << state.vel;
    }
    return os;
}

template <typename T, size_t N>
constexpr array<T, N> operator+(array<T, N> a, const array<T, N> &b) {
    transform(cbegin(a), cend(a), cbegin(b), begin(a), plus<int>{});
    return a;
}

int energy(const Coord &coord) {
    return transform_reduce(cbegin(coord), cend(coord), 0, plus<int>{},
                            [](const int x) { return abs(x); });
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    vector<Coord> pos;
    const regex pattern{"^<x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)>$"};
    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);
        pos.push_back(
            Coord{stoi(m[1].str()), stoi(m[2].str()), stoi(m[3].str())});
    }

    State state{pos, vector(sz(pos), Coord{0, 0, 0})};
    cerr << state << endl;
    return 0;
}
