#include <bits/stdc++.h>
using namespace std;
using Coord = tuple<int, int, int>;

template <typename T1, typename T2, typename T3>
ostream &operator<<(ostream &os, const tuple<T1, T2, T3> &x) {
    const auto [a, b, c] = x;
    os << '(' << a << ' ' << b << ' ' << c << ')';
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
constexpr tuple<T, T, T> operator+(const tuple<T, T, T> &lhs,
                                   const tuple<T, T, T> &rhs) {
    const auto [a, b, c] = lhs;
    const auto [x, y, z] = rhs;
    return {a + x, b + y, c + z};
}

vector<Coord> map_to_deltas(const string &s) {
    const int n = s.size();
    vector<Coord> ans;

    for (int i = 0; i < n;) {
        if (i < n - 1) {
            const string h = s.substr(i, 2);

            if (h == "se") {
                ans.emplace_back(0, -1, 1);
                i += 2;
                continue;
            }

            if (h == "sw") {
                ans.emplace_back(-1, 0, 1);
                i += 2;
                continue;
            }

            if (h == "ne") {
                ans.emplace_back(1, 0, -1);
                i += 2;
                continue;
            }

            if (h == "nw") {
                ans.emplace_back(0, 1, -1);
                i += 2;
                continue;
            }
        }

        if (s[i] == 'e') {
            ans.emplace_back(1, -1, 0);
            ++i;
            continue;
        }

        if (s[i] == 'w') {
            ans.emplace_back(-1, 1, 0);
            ++i;
            continue;
        }
    }

    return ans;
}

Coord follow_path(const Coord &origin, const vector<Coord> &deltas) {
    auto ans = origin;
    for (const auto &d : deltas) {
        ans = ans + d;
    }
    return ans;
}

int solve(const vector<string> &lines) {
    set<Coord> black;

    for (const auto &line : lines) {
        const auto p = follow_path({0, 0, 0}, map_to_deltas(line));
        if (black.count(p)) {
            black.erase(p);
        } else {
            black.insert(p);
        }
    }

    return black.size();
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    cout << solve(lines) << '\n';
    return 0;
}
