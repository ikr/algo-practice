#include <bits/stdc++.h>
using namespace std;
using Coord = tuple<int, int, int>;

template <typename T>
constexpr tuple<T, T, T> operator+(const tuple<T, T, T> &lhs,
                                   const tuple<T, T, T> &rhs) {
    const auto [a, b, c] = lhs;
    const auto [x, y, z] = rhs;
    return {a + x, b + y, c + z};
}

vector<Coord> map_to_deltas(const string &s) {

}

int solve(const vector<string> &lines) {
    set<Coord> black;

    return black.size();
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    cout << solve(lines) << '\n';
    return 0;
}
