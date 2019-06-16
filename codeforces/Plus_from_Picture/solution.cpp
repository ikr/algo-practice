#include <bits/stdc++.h>

using namespace std;

ostream &operator<<(ostream &os, const vector<int> &xs) {
    for (const auto x : xs) {
        cout << x << ' ';
    }

    return os;
}

struct RowCol final {
    int row;
    int col;
};

RowCol operator+(const RowCol p1, const RowCol p2) {
    return RowCol{p1.row + p2.row, p1.col + p2.col};
}

template <typename T> int intof(const T x) { return static_cast<int>(x); }

bool are_totals_ok(const vector<int> &totals) {
    if (totals.size() < 3 || totals[0] > 1 || totals.back() > 1) return false;

    vector<int> heapy = totals;
    partial_sort(heapy.begin(), heapy.begin() + 2, heapy.end(), greater<int>());

    return heapy[0] >= 3 && heapy[1] <= 1;
}

int index_of_max(const vector<int> &xs) {
    return intof(distance(xs.begin(), max_element(xs.begin(), xs.end())));
}

bool confirm_ray(const vector<string> &rows, const RowCol start,
                 const RowCol delta) {
    auto p = start;
    if (rows[p.row][p.col] != '*') return false;
    p = p + delta;

    bool interrupted = false;

    while (p.row < intof(rows.size()) && p.row >= 0 &&
           p.col < intof(rows[0].size()) && p.col >= 0) {
        const char c = rows[p.row][p.col];

        if (interrupted && c == '*') return false;
        if (c == '.') interrupted = true;

        p = p + delta;
    }

    return true;
}

bool confirm_a_cross(const vector<string> &rows, const int row, const int col) {
    if (rows[row][col] != '*') return false;

    const auto center = RowCol{row, col};
    const auto up = RowCol{-1, 0};
    const auto right = RowCol{0, 1};
    const auto down = RowCol{1, 0};
    const auto left = RowCol{0, -1};

    return confirm_ray(rows, center + up, up) &&
           confirm_ray(rows, center + right, right) &&
           confirm_ray(rows, center + down, down) &&
           confirm_ray(rows, center + left, left);
}

bool verify_cross_height(const vector<string> &rows, const int col,
                         const int height) {
    int stars_count = 0;

    for (const string &row : rows) {
        if (row[col] == '*') ++stars_count;
    }

    return stars_count == height;
}

bool verify_cross_size(const vector<string> &rows, const int row, const int col,
                       const int height, const int width) {
    return verify_cross_height(rows, col, height) &&
           (count(rows[row].begin(), rows[row].end(), '*') == width);
}

int main() {
    int rows_count;
    int cols_count;
    cin >> rows_count >> cols_count;

    vector<string> rows;
    vector<int> row_totals(rows_count);
    vector<int> col_totals(cols_count);

    for (int i = 0; i != rows_count; ++i) {
        string row;
        cin >> row;
        rows.push_back(row);

        for (int j = 0; j != cols_count; ++j) {
            if (row[j] == '*') {
                ++row_totals[i];
                ++col_totals[j];
            }
        }
    }

    const auto greater_than_zero = [](const int x) { return x > 0; };
    const int cross_row = index_of_max(row_totals);
    const int cross_col = index_of_max(col_totals);

    const bool verdict =
        are_totals_ok(row_totals) && are_totals_ok(col_totals) &&
        confirm_a_cross(rows, cross_row, cross_col) &&
        verify_cross_size(rows, cross_row, cross_col,
                          intof(count_if(row_totals.begin(), row_totals.end(),
                                         greater_than_zero)),
                          intof(count_if(col_totals.begin(), col_totals.end(),
                                         greater_than_zero)));

    cout << (verdict ? "YES" : "NO") << '\n';
}
