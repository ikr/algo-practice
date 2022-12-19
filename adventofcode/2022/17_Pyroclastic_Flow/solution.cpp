#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

constexpr char chof(const int x) { return static_cast<char>(x); }

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

int height(const Chamber &chamber) { return crbegin(chamber)->first + 1; }

vector<int> simulate_return_deltas(const string &mvs, const int num_rocks) {
    vector<int> result(num_rocks, -1);
    auto chamber = initial_chamber();

    for (int i_rock = 0, i_shape = 0, i_mv = 0; i_rock < num_rocks;
         ++i_rock, i_shape = (i_shape + 1) % sz(SHAPES_SEQ)) {
        Rock cur = move_by(SHAPES_SEQ[i_shape], {height(chamber) + 3, 2});

        for (;;) {
            {
                auto cur_ = move_by(cur, {0, mvs[i_mv++] == '<' ? -1 : 1});
                i_mv %= sz(mvs);
                if (!collides(cur_, chamber)) swap(cur_, cur);
            }

            {
                auto cur_ = move_by(cur, {-1, 0});
                if (collides(cur_, chamber)) {
                    const auto h_old = height(chamber);
                    chamber.insert(cbegin(cur), cend(cur));
                    result[i_rock] = height(chamber) - h_old;
                    break;
                } else {
                    swap(cur_, cur);
                }
            }
        }
    }

    return result;
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

bool is_at(const vector<int> &haystack, const vector<int> &needle,
           const int i) {
    for (int j = 0; j < sz(needle); ++j) {
        if (haystack[i + j] != needle[j]) return false;
    }

    return true;
}

int tail_period(const vector<int> &xs) {
    const auto marker_size = 16;
    const vector marker(cend(xs) - marker_size, cend(xs));
    assert(is_at(xs, marker, sz(xs) - marker_size));

    for (int i = sz(xs) - marker_size - 1; i >= 0; --i) {
        if (is_at(xs, marker, i)) {
            return sz(xs) - marker_size - i + 1;
        }
    }

    return -1;
}

int main() {
    string mvs;
    cin >> mvs;

    const auto LIM = 30000;
    const auto ds = simulate_return_deltas(mvs, LIM);

    const ll p = tail_period(ds);
    const vector period_elements(cend(ds) - p, cend(ds));
    cerr << "Period elements " << period_elements << endl;

    const auto r = 1000000000000LL - LIM;
    const ll result = accumulate(cbegin(ds), cend(ds), 0LL, plus<ll>{}) +
                      (r / p) * accumulate(cbegin(period_elements),
                                           cend(period_elements), 0) +
                      accumulate(cbegin(period_elements),
                                 cbegin(period_elements) + inof(r % p), 0);

    cout << result << '\n';
    return 0;
}
