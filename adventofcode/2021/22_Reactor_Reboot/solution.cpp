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

using ll = long long;
using pii = pair<int, int>;

enum class Switch { ON, OFF };

struct Box final {
    pii x;
    pii y;
    pii z;
};

struct Cmd final {
    Switch s;
    Box b;
};

ostream &operator<<(ostream &os, const Box &a) {
    os << '[' << a.x << ' ' << a.y << ' ' << a.z << ']';
    return os;
}

ostream &operator<<(ostream &os, const Cmd &a) {
    os << '{' << (a.s == Switch::ON ? "ON" : "OFF") << ' ' << a.b << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

pii parse_range(const string &src) {
    const auto parts = split("\\.\\.", src);
    assert(sz(parts) == 2);
    return {stoi(parts[0]), stoi(parts[1])};
}

Cmd parse_command(const string &src) {
    const auto [s, rest] = [&src]() -> pair<Switch, string> {
        if (src.substr(0, 3) == "on ") return {Switch::ON, src.substr(3)};
        assert(src.substr(0, 4) == "off ");
        return {Switch::OFF, src.substr(4)};
    }();

    const auto parts = split(",", rest);
    assert(sz(parts) == 3);
    return Cmd{s, parse_range(parts[0].substr(2)),
               parse_range(parts[1].substr(2)),
               parse_range(parts[2].substr(2))};
}

constexpr bool is_between(const pii ab, const int x) {
    return ab.first <= x && x <= ab.second;
}

optional<pii> intersection(const pii ab, const pii cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;

    assert(a <= b);
    assert(c <= d);
    if (d < a || c > b) return nullopt;

    array<int, 4> xs{a, b, c, d};
    sort(begin(xs), end(xs));
    return pii{xs[1], xs[2]};
}

int main() {
    vector<Cmd> commands;
    for (string line; getline(cin, line);) {
        commands.push_back(parse_command(line));
    }

    cerr << commands << endl;
    return 0;
}
