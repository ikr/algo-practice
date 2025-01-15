#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o) {
        os << "nullopt";
    } else {
        os << *o;
    }
    return os;
}

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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
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

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<int, int>;

enum class Dir { Up, Right, Down, Left };
static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

constexpr Dir dir_of(const Coord delta) {
    const int i = static_cast<int>(ranges::find(Delta, delta) - cbegin(Delta));
    assert(0 <= 1 && i < ssize(Delta));
    return static_cast<Dir>(i);
}

constexpr Coord delta_of(const Dir dir) {
    const int i = static_cast<int>(dir);
    assert(0 <= i && i < ssize(Delta));
    return Delta[i];
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

static constexpr int Limit = 100'000;

optional<int> limited_flood_fill_size(const vector<Coord> &path,
                                      const Coord u0) {
    set<Coord> visited(cbegin(path), cend(path));
    queue<Coord> q;
    q.push(u0);
    while (!empty(q)) {
        const auto u = q.front();
        q.pop();

        for (const auto delta : Delta) {
            const auto v = u + delta;
            if (visited.contains(v)) continue;
            visited.insert(v);
            if (sz(visited) > Limit) return nullopt;
            q.push(v);
        }
    }
    return sz(visited);
}

int solve(const vector<Coord> &path) {
    for (const auto &src :
         {Coord{-1, -1}, Coord{1, 1}, Coord{-1, 1}, Coord{1, -1}}) {
        const auto a = limited_flood_fill_size(path, src);
        if (a) return *a;
    }
    return -1;
}

int main() {
    vector<Coord> path{{0, 0}};
    Coord cur{0, 0};
    for (string line; getline(cin, line);) {
        const auto parts = split(" ", line);

        const auto dir = [&]() -> Dir {
            switch (parts[0][0]) {
            case 'U':
                return Dir::Up;
            case 'R':
                return Dir::Right;
            case 'D':
                return Dir::Down;
            default:
                assert(parts[0][0] == 'L');
                return Dir::Left;
            }
        }();

        const auto distance = stoi(parts[1]);
        for (int i = 1; i <= distance; ++i) {
            cur = cur + delta_of(dir);
            if (cur != path[0]) path.push_back(cur);
        }
    }

    cout << solve(path) << '\n';
    return 0;
}
