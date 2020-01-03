#include <bits/stdc++.h>

using namespace std;

using Col = int;
using ColRange = pair<Col, Col>;
using OptColRange = optional<pair<Col, Col>>;
using Row = int;
using Steps = long long;

enum class LevelAction {
    COLLECT_RIGHT_EXIT_LEFT, // ..ⓍOO..
    COLLECT_RIGHT_EXIT_RIGHT,
    COLLECT_LEFT_EXIT_LEFT, // ..OOⓍ..
    COLLECT_LEFT_EXIT_RIGHT,
    COLLECT_LEFT_RIGHT_EXIT_LEFT, // ..O←ⓍO..
    COLLECT_LEFT_RIGHT_EXIT_RIGHT,
    COLLECT_RIGHT_LEFT_EXIT_LEFT, // ..OⓍ→O..
    COLLECT_RIGHT_LEFT_EXIT_RIGHT
};

struct Island final {
    set<Col> exit_cols;
    vector<OptColRange> treasure_cols_by_row;
    int treasures;
};

struct IslandReduced final {
    Steps steps;
    Col start;
    set<Col> exit_cols;
    vector<ColRange> treasure_cols_by_row;
    int treasures;
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

    return {steps, start, isl.exit_cols, treasure_cols_by_row, isl.treasures};
}

set<LevelAction> inner_level_alternatives(const ColRange treasures,
                                          const Col start) {
    const auto [left, right] = treasures;

    if (start <= left) {
        return {LevelAction::COLLECT_RIGHT_EXIT_LEFT,
                LevelAction::COLLECT_LEFT_RIGHT_EXIT_RIGHT};
    }

    if (right <= start) {
        return {LevelAction::COLLECT_LEFT_EXIT_LEFT,
                LevelAction::COLLECT_LEFT_EXIT_RIGHT};
    }
}

Steps min_steps(const IslandReduced &isl) { return 0; }

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

    return {exit_columns, treasure_cols_by_row, k};
}

int main() { cout << min_steps(reduce_island(read_input())) << '\n'; }
