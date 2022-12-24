#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) { return static_cast<int>(x); }

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    vector<int> xs;
    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    const auto [hi, lo]= minmax_element(cbegin(xs), cend(xs));
    cerr << *hi << ' ' << *lo << endl;
    return 0;
}
