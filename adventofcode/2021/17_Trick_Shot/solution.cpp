#include <bits/stdc++.h>
#include <climits>
#include <numeric>
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

using pii = pair<int, int>;

template <typename T> struct mmin final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::min(a, b);
    }
};

static const string PREFIX{"target area: "};
static const string X_EQ{"x="};
static const string Y_EQ{"y="};

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

pii parse_range(const string &src) {
    const auto parts = split("\\.\\.", src);
    return {stoi(parts[0]), stoi(parts[1])};
}

set<pii> blob_of(const pii rx, const pii ry) {
    const auto [x_lo, x_hi] = rx;
    const auto [y_lo, y_hi] = ry;

    set<pii> result;
    for (auto x = x_lo; x <= x_hi; ++x) {
        for (auto y = y_lo; y <= y_hi; ++y) {
            result.emplace(x, y);
        }
    }
    return result;
}

constexpr int manhattan(const pii a, const pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int manhattan(const set<pii> &blob, const pii a) {
    return transform_reduce(cbegin(blob), cend(blob), INT_MAX, mmin<int>{},
                            [&](const pii b) { return manhattan(a, b); });
}

int highest_y(const pii rx, const pii ry) {
    const auto blob = blob_of(rx, ry);
    return manhattan(blob, {0, 0});
}

int main() {
    string line;
    getline(cin, line);

    const auto parts = split(", ", line.substr(PREFIX.size()));
    const auto rx = parse_range(parts[0].substr(X_EQ.size()));
    const auto ry = parse_range(parts[1].substr(Y_EQ.size()));

    cout << highest_y(rx, ry) << '\n';
    return 0;
}
