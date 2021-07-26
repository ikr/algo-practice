#include <bits/stdc++.h>

using namespace std;

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    R ans = init;

    for (auto it = first; it != last; ++it) {
        ans = binop(ans, unaop(*it));
    }

    return ans;
}

template <typename T> struct mmin {
    constexpr T operator()(const T &a, const T &b) const {
        return std::min(a, b);
    }
};

using Col = int;
using ColRange = pair<Col, Col>;
using OptColRange = optional<pair<Col, Col>>;
using Row = int;
using Steps = long long;

// By “exit lefty” we mean “stay on the same column, or go left, in order to
// exit”. While “exit right” means one must move right in order to exit.
//
enum class LevelAction {
    COLLECT_RIGHTY_EXIT_LEFTY, // ..ⓍOO..
    COLLECT_RIGHTY_EXIT_RIGHT,
    COLLECT_LEFTY_EXIT_LEFTY, // ..OOⓍ..
    COLLECT_LEFTY_EXIT_RIGHT,
    COLLECT_LEFT_RIGHT_EXIT_LEFTY, // ..O←ⓍO..
    COLLECT_LEFT_RIGHT_EXIT_RIGHT,
    COLLECT_RIGHT_LEFT_EXIT_LEFTY, // ..OⓍ→O..
    COLLECT_RIGHT_LEFT_EXIT_RIGHT
};

struct Exits final {
    vector<optional<Col>> lefty;
    vector<optional<Col>> right;
};

struct Island final {
    Exits exits;
    vector<OptColRange> treasure_cols_by_row;
};

struct IslandReduced final {
    Steps steps;
    Col start;
    Exits exits;
    vector<ColRange> treasure_cols_by_row;
};

template <typename T>
int trailing_empty_elements_count(const vector<optional<T>> &xs) {
    const auto it = find_if(xs.crbegin(), xs.crend(),
                            [](const optional<T> &x) { return !!x; });
    assert(it != xs.crend() && "trailing_empty_rows_count");
    return distance(xs.crbegin(), it);
}

IslandReduced reduce_island(const Island &isl) {
    const Col start =
        isl.treasure_cols_by_row[0]
            ? 0
            : **find_if(isl.exits.lefty.cbegin(), isl.exits.lefty.cend(),
                        [](const auto oc) { return !!oc; });

    const Steps steps =
        start + static_cast<Steps>(isl.treasure_cols_by_row.size()) -
        trailing_empty_elements_count(isl.treasure_cols_by_row) - 1;

    vector<ColRange> treasure_cols_by_row;

    for (auto it = isl.treasure_cols_by_row.cbegin();
         it != isl.treasure_cols_by_row.cend(); ++it) {
        if (!*it) continue;
        treasure_cols_by_row.push_back(**it);
    }

    return {steps, start, isl.exits, treasure_cols_by_row};
}

set<LevelAction> level_alternatives(const Exits &exits,
                                    const ColRange treasures, const Col start) {
    const auto [lo, hi] = treasures;

    if (start <= lo) { // ..ⓍOO..
        if (exits.lefty[hi] && *exits.lefty[hi] == hi)
            return {LevelAction::COLLECT_RIGHTY_EXIT_LEFTY};

        set<LevelAction> ans;
        if (exits.lefty[hi]) ans.insert(LevelAction::COLLECT_RIGHTY_EXIT_LEFTY);
        if (exits.right[hi]) ans.insert(LevelAction::COLLECT_RIGHTY_EXIT_RIGHT);
        return ans;
    } else if (hi <= start) { // ..OOⓍ..
        if (exits.lefty[lo] && *exits.lefty[lo] == lo)
            return {LevelAction::COLLECT_LEFTY_EXIT_LEFTY};

        set<LevelAction> ans;
        if (exits.lefty[lo]) ans.insert(LevelAction::COLLECT_LEFTY_EXIT_LEFTY);
        if (exits.right[lo]) ans.insert(LevelAction::COLLECT_LEFTY_EXIT_RIGHT);
        return ans;
    } else {
        set<LevelAction> ans;

        // ..O←ⓍO..
        if (exits.lefty[hi])
            ans.insert(LevelAction::COLLECT_LEFT_RIGHT_EXIT_LEFTY);
        if ((!exits.lefty[hi] || *exits.lefty[hi] != hi) && exits.right[hi])
            ans.insert(LevelAction::COLLECT_LEFT_RIGHT_EXIT_RIGHT);

        // ..OⓍ→O..
        if (exits.lefty[lo])
            ans.insert(LevelAction::COLLECT_RIGHT_LEFT_EXIT_LEFTY);
        if ((!exits.lefty[lo] || *exits.lefty[lo] != lo) && exits.right[lo])
            ans.insert(LevelAction::COLLECT_RIGHT_LEFT_EXIT_RIGHT);

        return ans;
    }
}

pair<Steps, Col> level_steps_and_exit(const Exits &exits,
                                      const ColRange treasures, const Col start,
                                      const LevelAction action) {
    const auto [lo, hi] = treasures;
    const Steps spread = hi - lo;

    const auto answer = [](const Steps sweep, const Col full,
                           const Col exit) -> pair<Steps, Col> {
        return {sweep + abs(full - exit), exit};
    };

    switch (action) {
    case LevelAction::COLLECT_RIGHTY_EXIT_LEFTY: // ..ⓍOO..
        return answer(hi - start, hi, *exits.lefty[hi]);
    case LevelAction::COLLECT_RIGHTY_EXIT_RIGHT:
        return answer(hi - start, hi, *exits.right[hi]);

    case LevelAction::COLLECT_LEFTY_EXIT_LEFTY: // ..OOⓍ..
        return answer(start - lo, lo, *exits.lefty[lo]);
    case LevelAction::COLLECT_LEFTY_EXIT_RIGHT:
        return answer(start - lo, lo, *exits.right[lo]);

    case LevelAction::COLLECT_LEFT_RIGHT_EXIT_LEFTY: // ..O←ⓍO..
        return answer(start - lo + spread, hi, *exits.lefty[hi]);
    case LevelAction::COLLECT_LEFT_RIGHT_EXIT_RIGHT:
        return answer(start - lo + spread, hi, *exits.right[hi]);

    case LevelAction::COLLECT_RIGHT_LEFT_EXIT_LEFTY: // ..OⓍ→O..
        return answer(hi - start + spread, lo, *exits.lefty[lo]);
    case LevelAction::COLLECT_RIGHT_LEFT_EXIT_RIGHT:
        return answer(hi - start + spread, lo, *exits.right[lo]);
    }

    assert(false && "level_steps_and_exit");
    return {-1, -1};
}

Steps terminal_level_steps(const ColRange treasures, const Col start) {
    const auto [lo, hi] = treasures;
    const Steps spread = hi - lo;

    if (start <= lo) return lo - start + spread;
    if (hi <= start) return start - hi + spread;

    assert(lo < start && start < hi && "terminal_level_steps");
    return min(start - lo + spread, hi - start + spread);
}

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        size_t ans = hash<T1>{}(p.first);
        ans = 31 * ans + hash<T2>{}(p.second);
        return ans;
    }
};

using Cache = unordered_map<pair<Row, Col>, Steps, PairHash<Row, Col>>;

Steps min_steps(const Col start, const Exits &exits,
                const vector<ColRange> &treasure_cols_by_row, const Row row,
                Cache &cache) {
    const pair<Row, Col> key{row, start};
    if (cache.count(key)) return cache.at(key);

    if (row == static_cast<Row>(treasure_cols_by_row.size() - 1)) {
        cache[key] = terminal_level_steps(treasure_cols_by_row.at(row), start);
    } else {
        const auto alts =
            level_alternatives(exits, treasure_cols_by_row.at(row), start);

        cache[key] = ttransform_reduce(
            alts.cbegin(), alts.cend(), numeric_limits<Steps>::max(),
            mmin<Steps>(),
            [start, &exits, &treasure_cols_by_row, row,
             &cache](const LevelAction action) {
                const auto [own_steps, own_exit] = level_steps_and_exit(
                    exits, treasure_cols_by_row.at(row), start, action);

                return own_steps + min_steps(own_exit, exits,
                                             treasure_cols_by_row, row + 1,
                                             cache);
            });
    }

    return cache.at(key);
}

Steps min_steps(const IslandReduced &isl) {
    Cache cache;

    return isl.steps +
           min_steps(isl.start, isl.exits, isl.treasure_cols_by_row, 0, cache);
}

bool can_exit_lefty(const set<Col> &exit_cols, const Col from_col) {
    const Col lo = *exit_cols.cbegin();
    return lo <= from_col;
}

bool can_exit_right(const set<Col> &exit_cols, const Col from_col) {
    const Col hi = *prev(exit_cols.cend());
    return from_col < hi;
}

Col lefty_exit(const set<Col> &exit_cols, const vector<bool> &is_exit_col,
               const Col from_col) {
    if (is_exit_col.at(from_col)) return from_col;
    const auto it = exit_cols.lower_bound(from_col);
    return *prev(it);
}

Col right_exit(const set<Col> &exit_cols, const Col from_col) {
    const auto it = exit_cols.upper_bound(from_col);
    assert(it != exit_cols.cend() && "right_exit");
    return *it;
}

Island read_input() {
    int n; // Rows
    int m; // Columns
    int k; // Treasures
    int q; // Safe columns
    cin >> n >> m >> k >> q;

    vector<set<Col>> treasure_column_sets_by_row(n);
    for (int i = 0; i != k; ++i) {
        int r1;
        int c1;
        cin >> r1 >> c1;

        assert(1 <= r1 && r1 <= n && "treasure row range");
        assert(1 <= c1 && c1 <= m && "treasure column range");

        treasure_column_sets_by_row[r1 - 1].insert(c1 - 1);
    }

    vector<OptColRange> treasure_cols_by_row(n);
    transform(treasure_column_sets_by_row.cbegin(),
              treasure_column_sets_by_row.cend(), treasure_cols_by_row.begin(),
              [](const set<Col> &cols_set) -> OptColRange {
                  if (cols_set.empty()) return nullopt;
                  return ColRange{*cols_set.cbegin(), *cols_set.crbegin()};
              });

    set<Col> exit_cols;
    vector<bool> is_exit_col(m, false);
    for (int i = 0; i != q; ++i) {
        int c1;
        cin >> c1;

        assert(1 <= c1 && c1 <= m && "exit column range");

        exit_cols.insert(c1 - 1);
        is_exit_col[c1 - 1] = true;
    }

    vector<optional<Col>> lefty(m, nullopt);
    vector<optional<Col>> right(m, nullopt);

    for (Col c = 0; c != m; ++c) {
        if (can_exit_lefty(exit_cols, c))
            lefty[c] = {lefty_exit(exit_cols, is_exit_col, c)};

        if (can_exit_right(exit_cols, c)) right[c] = {right_exit(exit_cols, c)};
    }

    return {{lefty, right}, treasure_cols_by_row};
}

int main() { cout << min_steps(reduce_island(read_input())) << '\n'; }
