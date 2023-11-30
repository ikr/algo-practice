#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using Coord = complex<ll>;
constexpr ll X(const Coord coord) { return coord.real(); }
constexpr ll Y(const Coord coord) { return coord.imag(); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> static_re_matches(const string &pattern_str,
                                 const string &input) {
    static const regex pattern{pattern_str};
    smatch m;
    regex_match(input, m, pattern);
    assert(!empty(m));

    vector<string> result(size(m) - 1);
    transform(cbegin(m) + 1, cend(m), begin(result),
              [](const auto &x) { return x.str(); });
    return result;
}

constexpr bool are_adjacent(const Coord a, const Coord b) {
    return norm(a - b) == 1;
}

static const string InputPattern{
    R"(^position=<( ?-?\d+), ( ?-?\d+)> velocity=<( ?-?\d+), ( ?-?\d+)>$)"};

int main() {
    vector<Coord> P;
    vector<Coord> V;

    for (string line; getline(cin, line);) {
        const auto tokens = static_re_matches(InputPattern, line);
        P.emplace_back(stoi(tokens[0]), stoi(tokens[1]));
        V.emplace_back(stoi(tokens[2]), stoi(tokens[3]));
    }

    const auto tick = [&]() -> void {
        ranges::transform(P, V, P.begin(),
                          [](const auto p, const auto v) { return p + v; });
    };

    const auto enough_of_points_have_a_neighbor = [&]() -> bool {
        return inof(ranges::count_if(P, [&](const auto p) {
                   return ranges::any_of(
                       P, [&](const auto q) { return are_adjacent(p, q); });
               })) > sz(P) * 4 / 5;
    };

    int elapsed{};
    for (;;) {
        if (enough_of_points_have_a_neighbor()) break;
        tick();
        ++elapsed;
    }

    const auto ox = X(*ranges::min_element(
        P, [](const auto p, const auto q) { return X(p) < X(q); }));

    const auto oy = Y(*ranges::min_element(
        P, [](const auto p, const auto q) { return Y(p) < Y(q); }));

    const auto H = 32;
    const auto W = 64;

    vector<string> grid(H, string(W, ' '));
    for (const auto &p : P) {
        grid[Y(p) - oy][X(p) - ox] = '#';
    }

    for (const auto &row : grid) {
        cout << row << '\n';
    }
    cout << elapsed << " ticks total\n";
    return 0;
}
