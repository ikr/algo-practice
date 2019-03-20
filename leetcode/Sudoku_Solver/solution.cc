#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace bruteforce {
struct Coord {
    Coord(int row, int col) : r{row}, c{col} {}

    int row() const { return r; }
    int col() const { return c; }

    Coord next_row() const { return {r + 1, c}; }
    Coord next_col() const { return {r, c + 1}; }

  private:
    int r;
    int c;
};

struct Solution {
    void solveSudoku(vector<vector<char>> &rows) const;

  private:
    using Rows = vector<vector<char>>;
    static constexpr int bsize = 3;
    static constexpr int gsize = bsize * bsize;
    static const vector<char> digits;

    static bool search_recur(Rows &rows);
    static bool is_valid(const Rows &rows, const Coord &coord, const char x);
    static vector<Coord> row_coords(const Coord &x);
    static vector<Coord> col_coords(const Coord &x);
    static vector<Coord> box_coords(const Coord &x);
    static unordered_set<char> elements_set(const Rows &rows,
                                            const vector<Coord> &coords);
    static optional<Coord> first_absent_coord(const Rows &rows);
    static vector<char> init_digits();
};

const vector<char> Solution::digits = Solution::init_digits();

void Solution::solveSudoku(Rows &rows) const { search_recur(rows); }

bool Solution::search_recur(Rows &rows) {
    optional<const Coord> v_coord = first_absent_coord(rows);

    if (!v_coord)
        return true;

    for (const char d : digits) {
        if (is_valid(rows, *v_coord, d)) {
            rows[v_coord->row()][v_coord->col()] = d;

            if (search_recur(rows))
                return true;

            rows[v_coord->row()][v_coord->col()] = '.';
        }
    }

    return false;
}

bool Solution::is_valid(const Rows &rows, const Coord &coord, char x) {
    if (elements_set(rows, row_coords(coord)).count(x))
        return false;

    if (elements_set(rows, col_coords(coord)).count(x))
        return false;

    if (elements_set(rows, box_coords(coord)).count(x))
        return false;

    return true;
}

vector<Coord> Solution::row_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        result.push_back({x.row(), i});
    }

    return result;
}

vector<Coord> Solution::col_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        result.push_back({i, x.col()});
    }

    return result;
}

vector<Coord> Solution::box_coords(const Coord &x) {
    const Coord o = {bsize * (x.row() / bsize), bsize * (x.col() / bsize)};
    const Coord o1 = o.next_row();
    const Coord o2 = o1.next_row();

    return {o,  o.next_col(),  o.next_col().next_col(),
            o1, o1.next_col(), o1.next_col().next_col(),
            o2, o2.next_col(), o2.next_col().next_col()};
}

unordered_set<char> Solution::elements_set(const Rows &rows,
                                           const vector<Coord> &coords) {
    unordered_set<char> result;

    for (const Coord &x : coords)
        if (rows[x.row()][x.col()] != '.')
            result.insert(rows[x.row()][x.col()]);

    return result;
}

optional<Coord> Solution::first_absent_coord(const Rows &rows) {
    for (int row = 0; row != gsize; ++row) {
        for (int col = 0; col != gsize; ++col) {
            if (rows[row][col] == '.')
                return {{row, col}};
        }
    }

    return nullopt;
}

vector<char> Solution::init_digits() {
    vector<char> result(gsize);
    iota(result.begin(), result.end(), '1');
    return result;
}
} // namespace bruteforce

namespace crook {
struct Coord {
    constexpr Coord(int row, int col) : r{row}, c{col} {}

    constexpr int row() const { return r; }
    constexpr int col() const { return c; }

    constexpr bool operator==(const Coord &other) const {
        return r == other.r && c == other.c;
    }

    constexpr bool operator!=(const Coord &other) const {
        return r != other.r || c != other.c;
    }

  private:
    int r;
    int c;
};

struct CoordHasher {
    constexpr int operator()(const Coord &coord) const {
        return coord.row() + 31 * coord.col();
    }
};

template <char N> struct Potential {
    constexpr Potential() : impl{} {}
    constexpr explicit Potential(const char only_one)
        : impl{1UL << (only_one - '1')} {}

    vector<char> elements() const;
    constexpr size_t size() const { return impl.count(); };
    void erase(const char el) { impl[el - '1'] = false; }
    void insert(const char el) { impl[el - '1'] = true; }
    static constexpr Potential full() { return bitset<N>{(1 << N) - 1}; }

  private:
    constexpr Potential(const bitset<N> &the_impl) : impl{the_impl} {}
    bitset<N> impl;
};

struct Solution {
    using Rows = vector<vector<char>>;
    void solveSudoku(Rows &rows) const;

  private:
    static constexpr int bsize = 3;
    static constexpr int gsize = bsize * bsize;
    using PotentialRows = vector<vector<Potential<gsize>>>;

    static PotentialRows all_potentials(const Rows &rows);
    static Potential<gsize> potential(const Rows &rows, const Coord &coord);
    static optional<PotentialRows> solve_recur(const PotentialRows &pots);
    static optional<Coord> min_ambiguous_coord(const PotentialRows &pots);
    static bool is_definite(const PotentialRows &pots);
    static void write_result(const PotentialRows &pots, Rows &rows);

    static PotentialRows assume_presence(const PotentialRows &pots,
                                         const Coord &coord, const char el);

    static vector<Coord> linked_coords(const Coord &x);
    static vector<Coord> row_coords(const Coord &x);
    static vector<Coord> col_coords(const Coord &x);
    static vector<Coord> box_coords(const Coord &x);
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (T x : xs) {
        os << x << ' ';
    }

    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &rows) {
    for (auto row : rows) {
        os << row << endl;
    }

    return os;
}

ostream &operator<<(ostream &os, const Coord &coord) {
    os << coord.row() << ',' << coord.col();
    return os;
}

template <char N> vector<char> Potential<N>::elements() const {
    vector<char> result{};

    if (!impl.count())
        return result;

    for (char i = 0; i != N; ++i) {
        if (impl[i])
            result.push_back(static_cast<char>('1' + i));
    }

    return result;
}

void Solution::solveSudoku(Rows &rows) const {
    auto result = solve_recur(all_potentials(rows));

    if (result)
        write_result(*result, rows);
}

void Solution::write_result(const PotentialRows &pots, Rows &rows) {
    for (int row = 0; row != gsize; ++row) {
        for (int col = 0; col != gsize; ++col) {
            rows[row][col] = pots[row][col].elements().back();
        }
    }
}

Solution::PotentialRows Solution::all_potentials(const Rows &rows) {
    PotentialRows result(gsize);

    for (auto &r : result) {
        r = vector<Potential<gsize>>(gsize);
    }

    for (int row = 0; row != gsize; ++row)
        for (int col = 0; col != gsize; ++col)
            result[row][col] = rows[row][col] == '.'
                                   ? potential(rows, {row, col})
                                   : Potential<gsize>{rows[row][col]};

    return result;
}

Potential<Solution::gsize> Solution::potential(const Rows &rows,
                                               const Coord &coord) {
    auto result = Potential<gsize>::full();

    for (const Coord &x : linked_coords(coord)) {
        const char el = rows[x.row()][x.col()];

        if (el != '.')
            result.erase(el);
    }

    return result;
}

optional<Solution::PotentialRows>
Solution::solve_recur(const PotentialRows &pots) {
    for (;;) {
        auto v_coord = min_ambiguous_coord(pots);

        if (!v_coord)
            return is_definite(pots) ? optional<Solution::PotentialRows>{pots}
                                     : nullopt;

        for (char el : pots[v_coord->row()][v_coord->col()].elements()) {
            auto result = solve_recur(assume_presence(pots, *v_coord, el));

            if (result)
                return result;
        }

        return nullopt;
    }
}

optional<Coord> Solution::min_ambiguous_coord(const PotentialRows &pots) {
    size_t min_size = gsize + 1;
    optional<Coord> result{nullopt};

    for (int row = 0; row != gsize; ++row) {
        for (int col = 0; col != gsize; ++col) {
            auto p = pots[row][col];

            if (p.size() > 1 && p.size() < min_size)
                result = {row, col};
        }
    }

    return result;
}

bool Solution::is_definite(const PotentialRows &pots) {
    for (const auto &r : pots) {
        for (const auto &p : r) {
            if (p.size() != 1)
                return false;
        }
    }

    return true;
}

Solution::PotentialRows Solution::assume_presence(const PotentialRows &pots,
                                                  const Coord &coord,
                                                  const char el) {
    PotentialRows result(pots);
    result[coord.row()][coord.col()] = Potential<gsize>{el};

    for (const Coord &x : linked_coords(coord))
        result[x.row()][x.col()].erase(el);

    return result;
}

vector<Coord> Solution::linked_coords(const Coord &x) {
    vector<Coord> result;

    for (auto xs : {row_coords(x), col_coords(x), box_coords(x)})
        result.insert(result.end(), make_move_iterator(xs.begin()),
                      make_move_iterator(xs.end()));

    return result;
}

vector<Coord> Solution::row_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        if (x.col() != i)
            result.push_back({x.row(), i});
    }

    return result;
}

vector<Coord> Solution::col_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        if (x.row() != i)
            result.push_back({i, x.col()});
    }

    return result;
}

vector<Coord> Solution::box_coords(const Coord &x) {
    vector<Coord> result;
    const Coord o = {bsize * (x.row() / bsize), bsize * (x.col() / bsize)};

    for (int row = 0; row != bsize; ++row) {
        for (int col = 0; col != bsize; ++col) {
            const Coord y{o.row() + row, o.col() + col};

            if (x != y)
                result.push_back(y);
        }
    }

    return result;
}
} // namespace crook

vector<vector<char>> input1() {
    return {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
}

vector<vector<char>> input2() {
    return {{'.', '.', '.', '.', '.', '7', '.', '.', '9'},
            {'.', '4', '.', '.', '8', '1', '2', '.', '.'},
            {'.', '.', '.', '9', '.', '.', '.', '1', '.'},
            {'.', '.', '5', '3', '.', '.', '.', '7', '2'},
            {'2', '9', '3', '.', '.', '.', '.', '5', '.'},
            {'.', '.', '.', '.', '.', '5', '3', '.', '.'},
            {'8', '.', '.', '.', '2', '3', '.', '.', '.'},
            {'7', '.', '.', '.', '5', '.', '.', '4', '.'},
            {'5', '3', '1', '.', '7', '.', '.', '.', '.'}};
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (T x : xs) {
        os << x << ' ';
    }

    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &rows) {
    for (auto row : rows) {
        os << row << endl;
    }

    return os;
}

int main() {
    auto rows = input1();
    cout << rows << endl;

    crook::Solution().solveSudoku(rows);
    cout << rows << endl;

    rows = input2();
    cout << rows << endl;

    crook::Solution().solveSudoku(rows);
    cout << rows << endl;

    return 0;
}
