#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    string instrs;
    getline(cin, instrs);

    string sep;
    getline(cin, sep);
    assert(empty(sep));

    map<string, vector<string>> g;

    for (string line; getline(cin, line);) {
        const auto u = line.substr(0, 3);
        const auto v1 = line.substr(7, 3);
        const auto v2 = line.substr(12, 3);
        g.emplace(u, vector{v1, v2});
    }

    int steps{};
    string cur{"AAA"};
    while (cur != "ZZZ") {
        for (const auto &instr : instrs) {
            if (instr == 'L') {
                cur = g[cur][0];
            } else {
                assert(instr == 'R');
                cur = g[cur][1];
            }
            ++steps;
        }
    }
    cout << steps << '\n';
    return 0;
}
