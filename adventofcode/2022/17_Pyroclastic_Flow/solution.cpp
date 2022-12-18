#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

int simulate_return_tower_height(const string &mvs, const int num_rocks) {
    return -1;
}

int main() {
    string mvs;
    cin >> mvs;
    cout << simulate_return_tower_height(mvs, 2022);
    return 0;
}
