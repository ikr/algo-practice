#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using Coord = array<int, 3>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    vector<Coord> bodies;
    const regex pattern{"^<x=(-?[0-9]+), y=(-?[0-9]+), z=(-?[0-9]+)>$"};
    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);
        bodies.push_back(
            Coord{stoi(m[1].str()), stoi(m[2].str()), stoi(m[3].str())});
    }

    cerr << bodies << endl;
    return 0;
}
