#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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
        os << "pos=" << state.pos[i] << " vel=" << state.vel[i] << '\n';
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

int total_energy(const vector<Coord> &pos, const vector<Coord> &vel) {
    return transform_reduce(
        cbegin(pos), cend(pos), cbegin(vel), 0, plus<int>{},
        [](const Coord &a, const Coord &b) { return energy(a) * energy(b); });
}

pair<Coord, Coord> velocity_deltas(const Coord &a, const Coord &b) {
    Coord u{0, 0, 0};
    Coord v{0, 0, 0};

    for (int i = 0; i < sz(a); ++i) {
        if (a[i] < b[i]) {
            u[i] = 1;
            v[i] = -1;
        } else if (a[i] > b[i]) {
            u[i] = -1;
            v[i] = 1;
        }
    }

    return {u, v};
}

State evolve(const State &s) {
    auto vel = s.vel;
    for (int i = 0; i < sz(vel) - 1; ++i) {
        for (int j = i + 1; j < sz(vel); ++j) {
            const auto [u, v] = velocity_deltas(s.pos[i], s.pos[j]);
            vel[i] = vel[i] + u;
            vel[j] = vel[j] + v;
        }
    }

    auto pos = s.pos;
    transform(cbegin(pos), cend(pos), cbegin(vel), begin(pos),
              [](const Coord &a, const Coord &b) { return a + b; });
    return {pos, vel};
}

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

    for (int i = 1; i <= 1000; ++i) {
        state = evolve(state);
        cout << "E" << i << ": " << total_energy(state.pos, state.vel) << '\n'
             << state << '\n';
    }

    return 0;
}
