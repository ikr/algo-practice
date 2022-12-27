#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (line == "") break;
        grid.push_back(line);
    }

    for (const auto &row : grid) cerr << row << endl;

    string command_source;
    cin >> command_source;

    cerr << command_source << endl;
    return 0;
}
