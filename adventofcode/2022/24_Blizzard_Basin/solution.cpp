#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using Coord = pair<int, int>;

enum class Dir { U = 0, R = 1, D = 2, L = 3 };

static constexpr array<Coord, 4> DELTAS{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                                        Coord{0, -1}};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

struct Blizzards final {
    int H;
    int W;
    array<set<Coord>, 4> xss;

    Blizzards() : H{}, W{} { xss.fill(set<Coord>()); }

    Blizzards tick() const {
        Blizzards result;
        result.H = H;
        result.W = W;

        for (int i = 0; i < sz(DELTAS); ++i) {
            for (const auto &x : xss[i]) {
                auto [ro, co] = x + DELTAS[i];
                if (i % 2) {
                    co = ((co % W) + W) % W;
                } else {
                    ro = ((ro % H) + H) % H;
                }
                result.xss[i].emplace(ro, co);
            }
        }
        return result;
    }

    bool operator==(const Blizzards &o) const {
        if (&o == this) return true;
        return H == o.H && W == o.W && xss == o.xss;
    }
};

ostream &operator<<(ostream &os, const Blizzards &bs) {
    os << pair{bs.H, bs.W} << ' ' << bs.xss;
    return os;
}

vector<Blizzards> all_blizzard_configurations(const Blizzards &bs) {
    vector<Blizzards> result{bs};
    for (;;) {
        auto bs_ = result.back().tick();
        if (bs_ == result[0]) break;
        result.emplace_back(move(bs_));
    }
    for (const auto &a : result) {
        cerr << a << endl;
    }
    return result;
}

int main() {
    Blizzards bs{};

    for (string line; getline(cin, line);) {
        if (line.substr(0, 3) == "#.#" || line.substr(0, 3) == "###") continue;
        line = line.substr(1, sz(line) - 2);
        cerr << line << endl;

        for (int co = 0; co < sz(line); ++co) {
            switch (line[co]) {
            case '^':
                bs.xss[inof(Dir::U)].emplace(bs.H, co);
                break;
            case '>':
                bs.xss[inof(Dir::R)].emplace(bs.H, co);
                break;
            case 'v':
                bs.xss[inof(Dir::D)].emplace(bs.H, co);
                break;
            case '<':
                bs.xss[inof(Dir::L)].emplace(bs.H, co);
                break;
            }
        }

        ++bs.H;
        bs.W = sz(line);
    }

    cerr << bs << endl << endl;
    all_blizzard_configurations(bs);
    return 0;
}
