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

struct Cmd final {
    Switch s;
    pii x;
    pii y;
    pii z;
};

ostream &operator<<(ostream &os, const Cmd &a) {
    os << '{' << (a.s == Switch::ON ? "ON" : "OFF") << ' ' << a.x << ' ' << a.y
       << ' ' << a.z << '}';
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

int main() {
    vector<Cmd> commands;
    for (string line; getline(cin, line);) {
        commands.push_back(parse_command(line));
    }

    vector<vector<vector<bool>>> on(101, vector(101, vector(101, false)));

    for (const auto &c : commands) {
        for (int i = 0; i < sz(on); ++i) {
            for (int j = 0; j < sz(on[i]); ++j) {
                for (int k = 0; k < sz(on[i][j]); ++k) {
                    const auto x = i - 50;
                    const auto y = j - 50;
                    const auto z = k - 50;

                    if (is_between(c.x, x) && is_between(c.y, y) &&
                        is_between(c.z, z)) {
                        on[i][j][k] = c.s == Switch::ON;
                    }
                }
            }
        }
    }

    int ans{};
    for (int i = 0; i < sz(on); ++i) {
        for (int j = 0; j < sz(on[i]); ++j) {
            ans += inof(count(cbegin(on[i][j]), cend(on[i][j]), true));
        }
    }
    cout << ans << '\n';
    return 0;
}
