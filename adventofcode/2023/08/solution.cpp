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

    set<string> starting_s;
    set<string> ending_s;

    for (string line; getline(cin, line);) {
        const auto u = line.substr(0, 3);
        const auto v1 = line.substr(7, 3);
        const auto v2 = line.substr(12, 3);
        g.emplace(u, vector{v1, v2});

        if (u.back() == 'A') starting_s.insert(u);
        if (v1.back() == 'Z') ending_s.insert(v1);
        if (v2.back() == 'Z') ending_s.insert(v2);
    }
    assert(sz(starting_s) == sz(ending_s));
    cerr << "sz:" << sz(starting_s) << endl;

    const vector<string> starting(cbegin(starting_s), cend(starting_s));
    const vector<string> ending(cbegin(ending_s), cend(ending_s));

    cerr << "starting:" << starting << " ending:" << ending << endl;

    int steps{};
    auto cur = starting;
    while (cur != ending) {
        for (const auto &instr : instrs) {
            for (auto &u : cur) {
                if (instr == 'L') {
                    u = g[u][0];
                } else {
                    assert(instr == 'R');
                    u = g[u][1];
                }
            }
            ranges::sort(cur);
            ++steps;
            cerr << "cur:" << cur << " steps:" << steps << endl;
        }
    }
    cout << steps << '\n';
    return 0;
}
