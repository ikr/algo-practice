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

using Coord = pair<int, int>;

static const string InputPattern{
    R"(^position=<( ?-?\d+), ( ?-?\d+)> velocity=<( ?-?\d+), ( ?-?\d+)>$)"};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> static_re_matches(const string &pattern_str,
                                 const string &input) {
    static const regex pattern{pattern_str};
    smatch m;
    regex_match(input, m, pattern);
    assert(!empty(m));

    vector<string> result(size(m) - 1);
    transform(cbegin(m) + 1, cend(m), begin(result),
              [](const auto &x) { return x.str(); });
    return result;
}

int main() {
    for (string line; getline(cin, line);) {
        const auto tokens = static_re_matches(InputPattern, line);
        const Coord position{stoi(tokens[0]), stoi(tokens[1])};
        const Coord velocity{stoi(tokens[2]), stoi(tokens[3])};
        cerr << position << ' ' << velocity << endl;
    }

    return 0;
}
