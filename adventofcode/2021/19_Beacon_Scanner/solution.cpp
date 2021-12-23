#include <bits/stdc++.h>
using namespace std;

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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const vector<array<T, N>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Tri = array<int, 3>;

bool is_scanner_sep_line(const string &line) {
    return line.find("--- scanner ") == 0;
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int main() {
    vector<vector<Tri>> data;
    vector<Tri> curr;

    for (string line; getline(cin, line);) {
        if (line.empty()) continue;
        if (is_scanner_sep_line(line)) {
            if (curr.empty()) continue;
            data.push_back(curr);
            curr.clear();
            continue;
        }

        const auto xs = split(",", line);
        Tri t;
        transform(cbegin(xs), cend(xs), begin(t),
                  [](const auto &x) { return stoi(x); });
        curr.push_back(t);
    }

    assert(!curr.empty());
    data.push_back(curr);

    cerr << "Read measurements of " << sz(data) << " scanners\n";
    for (const auto &ds : data) {
        cerr << sz(ds) << ' ';
    }
    cerr << '\n';

    for (const auto &ds : data) {
        cerr << ds << '\n';
    }

    return 0;
}
