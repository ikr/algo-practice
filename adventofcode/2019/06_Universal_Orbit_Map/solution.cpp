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

using Graph = multimap<string, string>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    Graph follows;
    set<string> vertices;

    for (string line; getline(cin, line);) {
        const auto sep = line.find(')');
        const auto u = line.substr(0, sep);
        const auto v = line.substr(sep + 1);
        follows.emplace(v, u);
        vertices.insert(u);
        vertices.insert(v);
    }

    return 0;
}
