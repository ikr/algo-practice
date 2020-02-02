#include <bits/stdc++.h>
#include <numeric>

using namespace std;

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

struct Island final {
    set<Col> exit_cols;
    vector<OptColRange> treasure_cols_by_row;
};

struct IslandReduced final {
    Steps steps;
    Col start;
    set<Col> exit_cols;
    vector<ColRange> treasure_cols_by_row;
};

IslandReduced reduce_island(const Island &isl) {
    const auto start =
        isl.treasure_cols_by_row[0] ? 0 : isl.treasure_cols_by_row[0]->first;

    Steps steps = start;
    vector<ColRange> treasure_cols_by_row;

    for (auto it = isl.treasure_cols_by_row.cbegin();
         it != isl.treasure_cols_by_row.cend(); ++it) {
        if (!*it) continue;
        ++steps;
        treasure_cols_by_row.push_back(**it);
    }

    return {steps, start, isl.exit_cols, treasure_cols_by_row};
}

bool can_exit_lefty(const set<Col> &exit_cols, const Col from_col) {
    assert(!exit_cols.empty() && "can_exit_lefty");
    const Col lo = *exit_cols.cbegin();
    return lo <= from_col;
}

bool can_exit_right(const set<Col> &exit_cols, const Col from_col) {
    assert(!exit_cols.empty() && "can_exit_right");
    const Col hi = *exit_cols.cend();
    return from_col < hi;
}

set<LevelAction> level_alternatives(const set<Col> &exit_cols,
                                    const ColRange treasures, const Col start) {
    const auto [lo, hi] = treasures;
    set<LevelAction> ans;

    if (start <= lo) { // ..ⓍOO..
        if (can_exit_lefty(exit_cols, hi))
            ans.insert(LevelAction::COLLECT_RIGHTY_EXIT_LEFTY);
        if (can_exit_right(exit_cols, hi))
            ans.insert(LevelAction::COLLECT_RIGHTY_EXIT_RIGHT);
    } else if (hi <= start) { // ..OOⓍ..
        if (can_exit_lefty(exit_cols, lo))
            ans.insert(LevelAction::COLLECT_LEFTY_EXIT_LEFTY);
        if (can_exit_right(exit_cols, lo))
            ans.insert(LevelAction::COLLECT_LEFTY_EXIT_RIGHT);
    } else {
        assert(lo < start && start < hi);

        // ..O←ⓍO..
        if (can_exit_lefty(exit_cols, hi))
            ans.insert(LevelAction::COLLECT_LEFT_RIGHT_EXIT_LEFTY);
        if (can_exit_right(exit_cols, hi))
            ans.insert(LevelAction::COLLECT_LEFT_RIGHT_EXIT_RIGHT);

        // ..OⓍ→O..
        if (can_exit_lefty(exit_cols, lo))
            ans.insert(LevelAction::COLLECT_RIGHT_LEFT_EXIT_LEFTY);
        if (can_exit_right(exit_cols, lo))
            ans.insert(LevelAction::COLLECT_RIGHT_LEFT_EXIT_RIGHT);
    }

    assert(!ans.empty());
    return ans;
}

Col lefty_exit(const set<Col> &exit_cols, const Col from_col) {
    const auto it = lower_bound(exit_cols.cbegin(), exit_cols.cend(), from_col);

    if (it != exit_cols.cend() && *it == from_col) return from_col;
    return *prev(it);
}

Col right_exit(const set<Col> &exit_cols, const Col from_col) {
    const auto it = upper_bound(exit_cols.cbegin(), exit_cols.cend(), from_col);
    assert(it != exit_cols.cend() && "right_exit");
    return *it;
}

pair<Steps, Col> level_steps_and_exit(const set<Col> &exit_cols,
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
        return answer(hi - start, hi, lefty_exit(exit_cols, hi));
    case LevelAction::COLLECT_RIGHTY_EXIT_RIGHT:
        return answer(hi - start, hi, right_exit(exit_cols, hi));

    case LevelAction::COLLECT_LEFTY_EXIT_LEFTY: // ..OOⓍ..
        return answer(start - lo, lo, lefty_exit(exit_cols, lo));
    case LevelAction::COLLECT_LEFTY_EXIT_RIGHT:
        return answer(start - lo, lo, right_exit(exit_cols, lo));

    case LevelAction::COLLECT_LEFT_RIGHT_EXIT_LEFTY: // ..O←ⓍO..
        return answer(start - lo + spread, hi, lefty_exit(exit_cols, hi));
    case LevelAction::COLLECT_LEFT_RIGHT_EXIT_RIGHT:
        return answer(start - lo + spread, hi, right_exit(exit_cols, hi));

    case LevelAction::COLLECT_RIGHT_LEFT_EXIT_LEFTY: // ..OⓍ→O..
        return answer(hi - start + spread, lo, lefty_exit(exit_cols, lo));
    case LevelAction::COLLECT_RIGHT_LEFT_EXIT_RIGHT:
        return answer(hi - start + spread, lo, right_exit(exit_cols, lo));
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

Steps min_steps(const Col start, const set<Col> &exit_cols,
                const vector<ColRange> &treasure_cols_by_row, const Row row) {
    if (row == static_cast<Row>(treasure_cols_by_row.size() - 1)) {
        return terminal_level_steps(treasure_cols_by_row.at(row), start);
    }

    const auto alts =
        level_alternatives(exit_cols, treasure_cols_by_row.at(row), start);

    return transform_reduce(
        alts.cbegin(), alts.cend(), numeric_limits<Steps>::max(), mmin<Steps>(),
        [start, &exit_cols, &treasure_cols_by_row,
         row](const LevelAction action) {
            const auto [own_steps, own_exit] = level_steps_and_exit(
                exit_cols, treasure_cols_by_row.at(row), start, action);

            return own_steps + min_steps(own_exit, exit_cols,
                                         treasure_cols_by_row, row + 1);
        });
}

Steps min_steps(const IslandReduced &isl) {
    return isl.steps +
           min_steps(isl.start, isl.exit_cols, isl.treasure_cols_by_row, 0);
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
        treasure_column_sets_by_row[r1 - 1].insert(c1 - 1);
    }

    vector<OptColRange> treasure_cols_by_row(n);
    transform(treasure_column_sets_by_row.cbegin(),
              treasure_column_sets_by_row.cend(), treasure_cols_by_row.begin(),
              [](const set<Col> &cols_set) -> OptColRange {
                  if (cols_set.empty()) return nullopt;
                  return ColRange{*cols_set.cbegin(), *cols_set.crbegin()};
              });

    set<Col> exit_columns;
    for (int i = 0; i != q; ++i) {
        int c1;
        cin >> c1;
        exit_columns.insert(c1 - 1);
    }

    assert(!exit_columns.empty());
    return {exit_columns, treasure_cols_by_row};
}

int main() { cout << min_steps(reduce_island(read_input())) << '\n'; }
