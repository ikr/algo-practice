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

using MatQuant = pair<string, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

MatQuant parse_material_quantity(const string &src) {
    const auto parts = split(" ", src);
    return {parts[1], stoi(parts[0])};
}

vector<MatQuant> parse_material_quantities(const string &src) {
    const auto parts = split(", ", src);
    vector<MatQuant> result(sz(parts));
    transform(cbegin(parts), cend(parts), begin(result),
              parse_material_quantity);
    return result;
}

int main() {
    for (string line; getline(cin, line);) {
        const auto parts = split(" => ", line);
        const auto input = parse_material_quantities(parts[0]);
        const auto output = parse_material_quantity(parts[1]);

        cerr << input << " → " << output << endl;
    }

    return 0;
}
