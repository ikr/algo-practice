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
using tri = tuple<int, int, int>;

enum class Switch { ON, OFF };

struct Box final {
    pii x;
    pii y;
    pii z;

    bool operator==(const Box &o) const {
        return x == o.x && y == o.y && z == o.z;
    }

    bool operator!=(const Box &o) const { return !(*this == o); }
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

constexpr array<int, 2> as_arr(const pii &a) { return {a.first, a.second}; }

constexpr bool is_between(const pii ab, const int x) {
    return ab.first <= x && x <= ab.second;
}

constexpr bool contains(const Box &b, const tri &p) {
    const auto [x, y, z] = p;
    return is_between(b.x, x) && is_between(b.y, y) && is_between(b.z, z);
}

constexpr bool contains(const Box &a, const Box &b) {
    for (const auto x : as_arr(b.x)) {
        for (const auto y : as_arr(b.y)) {
            for (const auto z : as_arr(b.z)) {
                if (!contains(a, {x, y, z})) return false;
            }
        }
    }
    return true;
}

vector<Box> cut_out_subbox(Box src, const Box &del) {
    assert(contains(src, del));
    assert(src != del);
    vector<Box> result;

    if (src.x.first < del.x.first) {
        result.push_back(Box{pii{src.x.first, del.x.first - 1}, src.y, src.z});
        src.x.first = del.x.first;
    }

    if (del.x.second < src.x.second) {
        result.push_back(
            Box{pii{del.x.second + 1, src.x.second}, src.y, src.z});
        src.x.second = del.x.second;
    }

    if (src.y.first < del.y.first) {
        result.push_back(Box{src.x, pii{src.y.first, del.y.first - 1}, src.z});
        src.y.first = del.y.first;
    }

    if (del.y.second < src.y.second) {
        result.push_back(
            Box{src.x, pii{del.y.second + 1, src.y.second}, src.z});
        src.y.second = del.y.second;
    }

    return result;
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

optional<Box> intersection(const Box &a, const Box &b) {
    const auto x = intersection(a.x, b.x);
    if (!x) return nullopt;

    const auto y = intersection(a.y, b.y);
    if (!y) return nullopt;

    const auto z = intersection(a.z, b.z);
    if (!z) return nullopt;

    return Box{*x, *y, *z};
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

pii parse_range(const string &src) {
    const auto parts = split("\\.\\.", src);
    assert(sz(parts) == 2);

    const auto a = stoi(parts[0]);
    const auto b = stoi(parts[1]);
    assert(a <= b);

    return {a, b};
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

int main() {
    vector<Cmd> commands;
    for (string line; getline(cin, line);) {
        commands.push_back(parse_command(line));
    }

    return 0;
}
