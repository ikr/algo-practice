#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = array<int, 3>;

struct State final {
    vector<Coord> pos;
    vector<Coord> vel;
};

template <typename T, size_t N>
constexpr array<T, N> operator+(array<T, N> a, const array<T, N> &b) {
    transform(cbegin(a), cend(a), cbegin(b), begin(a), plus<int>{});
    return a;
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

template <typename T>
bool is_at(const vector<T> &haystack, const vector<T> &needle, const int i) {
    for (int j = 0; j < sz(needle); ++j) {
        if (haystack[i + j] != needle[j]) return false;
    }

    return true;
}

template <typename T> int tail_period(const vector<T> &xs) {
    const auto marker_size = 32;
    const vector marker(cend(xs) - marker_size, cend(xs));
    assert(is_at(xs, marker, sz(xs) - marker_size));

    for (int i = sz(xs) - marker_size - 1; i >= 0; --i) {
        if (is_at(xs, marker, i)) {
            return sz(xs) - marker_size - i;
        }
    }

    return -1;
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
    vector<vector<pair<int, int>>> traces(3 * sz(pos));

    const auto log_traces = [&]() -> void {
        for (int j = 0; j < sz(pos); ++j) {
            for (int k = 0; k < 3; ++k) {
                traces[3 * j + k].emplace_back(state.pos[j][k],
                                               state.vel[j][k]);
            }
        }
    };
    log_traces();

    for (int i = 1; i <= 1'000'000; ++i) {
        state = evolve(state);
        log_traces();
    }

    ll ans = 1;
    for (int j = 0; j < sz(traces); ++j) {
        const auto p = tail_period(traces[j]);
        ans = lcm(ans, p);
        cerr << p << endl;
    }

    cout << ans << '\n';
    return 0;
}
