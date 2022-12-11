#include <bits/stdc++.h>
using namespace std;

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

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

struct Monkey final {
    queue<int> q;
};

auto strings_to_ints(const vector<string> &xs) {
    vector<int> result(sz(xs));
    transform(cbegin(xs), cend(xs), begin(result),
              [](const auto &x) { return stoi(x); });
    return result;
}

Monkey read_monkey() {
    string line;
    getline(cin, line); // Monkey X:

    getline(cin, line);
    const auto xs = strings_to_ints(
        split(", ", line.substr(sz(string{"  Starting items: "}))));
    cerr << xs << endl;

    getline(cin, line); // "  Operation: new = old "
    getline(cin, line); // "  Test: divisible by "
    getline(cin, line); // "    If true: throw to monkey "
    getline(cin, line); // "    If false: throw to monkey "

    return {{}};
}

int main() {
    for (;;) {
        read_monkey();
        string line;
        if (!getline(cin, line)) break;
    }
    return 0;
}
