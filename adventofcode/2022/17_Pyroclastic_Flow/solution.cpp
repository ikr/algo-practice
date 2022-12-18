#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Shape = vector<Coord>;
using Rock = vector<Coord>;
using Chamber = set<Coord>;

static constexpr int CO_MAX = 6;

static const Shape MINUS_SHAPE{{0, 0}, {0, 1}, {0, 2}, {0, 3}};
static const Shape PLUS_SHAPE{{2, 1}, {1, 0}, {1, 1}, {1, 2}, {0, 1}};
static const Shape ANGLE_SHAPE{{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}};
static const Shape PIPE_SHAPE{{0, 0}, {1, 0}, {2, 0}, {3, 0}};
static const Shape SQUARE_SHAPE{{1, 0}, {1, 1}, {0, 0}, {0, 1}};

static const vector<Shape> SHAPES_SEQ{MINUS_SHAPE, PLUS_SHAPE, ANGLE_SHAPE,
                                      PIPE_SHAPE, SQUARE_SHAPE};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int RO(const Coord roco) { return roco.first; }

constexpr int CO(const Coord roco) { return roco.second; }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

Chamber initial_chamber() {
    set<Coord> result;
    for (int co = 0; co < 7; ++co) {
        result.emplace(-1, co);
    }
    return result;
}

vector<Coord> move_by(const vector<Coord> &obj, const Coord vec) {
    vector<Coord> result(sz(obj));
    transform(cbegin(obj), cend(obj), begin(result),
              [vec](const Coord roco) { return roco + vec; });
    return result;
}

bool collides(const Rock &rock, const Chamber &chamber) {
    return any_of(cbegin(rock), cend(rock), [&chamber](const Coord a) {
        if (CO(a) < 0 || CO_MAX < CO(a)) return true;
        return chamber.find(a) != cend(chamber);
    });
}

int simulate_return_tower_height(const string &mvs, const int num_rocks) {
    auto chamber = initial_chamber();
    const auto chamber_height = [&chamber]() -> int {
        return crbegin(chamber)->first + 1;
    };

    for (int i_rock = 0, i_shape = 0, i_mv = 0; i_rock < num_rocks;
         ++i_rock, i_shape = (i_shape + 1) % sz(SHAPES_SEQ)) {
        Rock cur = move_by(SHAPES_SEQ[i_shape], {chamber_height() + 3, 2});

        for (;;) {
            {
                auto cur_ = move_by(cur, {0, mvs[i_mv++] == '<' ? -1 : 1});
                i_mv %= sz(mvs);
                if (!collides(cur_, chamber)) swap(cur_, cur);
            }

            {
                auto cur_ = move_by(cur, {-1, 0});
                if (collides(cur_, chamber)) {
                    chamber.insert(cbegin(cur), cend(cur));
                    break;
                } else {
                    swap(cur_, cur);
                }
            }
        }
    }

    return chamber_height();
}

int main() {
    string mvs;
    cin >> mvs;
    cout << simulate_return_tower_height(mvs, 2022) << '\n';
    return 0;
}
