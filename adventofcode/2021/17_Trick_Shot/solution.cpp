#include <bits/stdc++.h>
#include <climits>
#include <numeric>
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

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

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

// Find a positive int solution n of the equation n(n + 1)/2 = d
optional<int> find_n(const int d) {
    for (int n = 1; n < d; ++n) {
        if (n * (n + 1LL) / 2LL == llof(d)) return n;
    }
    return nullopt;
}

int highest_y(const pii rx, const pii ry) {
    const auto [x_lo, x_hi] = rx;
    const auto [y_lo, y_hi] = ry;

    int max_vy = -1;

    for (auto x = x_lo; x <= x_hi; ++x) {
        const auto vx = find_n(x);
        if (!vx) continue;
        const auto t_lo = *vx;

        for (auto y = y_lo; y <= y_hi; ++y) {
            for (auto t = t_lo; t < 1000; ++t) {
                const auto y0 = y + t * (t + 1) / 2;
                const auto vy = find_n(y0);
                if (vy) max_vy = max(max_vy, *vy);
            }
        }
    }

    return max_vy * (max_vy + 1) / 2;
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
