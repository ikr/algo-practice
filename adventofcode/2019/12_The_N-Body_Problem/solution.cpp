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

template <typename T> ll period(const vector<T> &trace) {
    const auto shift = 0;
    const auto &a0 = trace[shift];
    for (int i = shift + 1; i < sz(trace); ++i) {
        if (trace[i] == a0) return i - shift;
    }
    return 0;
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
        const auto p = period(traces[j]);
        ans = lcm(ans, p);
        cerr << p << endl;
    }

    cout << ans << '\n';
    return 0;
}
