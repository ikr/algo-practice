#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

ll steps_for(const string &instrs, const vector<pair<int, int>> &g,
             const int id) {
    int steps{};
    auto u = id;

    while (u % 26 != 25) {
        for (const auto &instr : instrs) {
            if (instr == 'L') {
                u = g[u].first;
            } else {
                assert(instr == 'R');
                u = g[u].second;
            }
            ++steps;
            if (u % 26 == 25) break;
        }
    }
    cerr << "steps for " << id << ": " << steps << endl;
    return steps;
}

int v_id(const string &x) {
    int m = 1;
    int result{};
    for (const auto c : x | ranges::views::reverse) {
        result += m * inof(c - 'A');
        m *= 26;
    }
    return result;
}

int main() {
    string instrs;
    getline(cin, instrs);

    string sep;
    getline(cin, sep);
    assert(empty(sep));

    vector<pair<int, int>> g(20'000);

    set<int> starting_s;

    for (string line; getline(cin, line);) {
        const auto u = line.substr(0, 3);
        const auto v1 = line.substr(7, 3);
        const auto v2 = line.substr(12, 3);
        g[v_id(u)] = pair{v_id(v1), v_id(v2)};

        if (u.back() == 'A') starting_s.insert(v_id(u));
    }

    const vector<int> starting(cbegin(starting_s), cend(starting_s));
    vector<ll> steps(sz(starting));
    ranges::transform(starting, begin(steps),
                      [&](const auto id) { return steps_for(instrs, g, id); });
    cout << accumulate(cbegin(steps), cend(steps), 1LL,
                       [](const ll acc, const ll x) { return lcm(acc, x); })
         << '\n';
    return 0;
}
