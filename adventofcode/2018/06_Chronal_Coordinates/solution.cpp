#include <bits/stdc++.h>
using namespace std;
using namespace std::ranges::views;

using Coord = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    for (string line; getline(cin, line);) {
        cerr << '[' << line << ']' << endl;
    }

    return 0;
}
