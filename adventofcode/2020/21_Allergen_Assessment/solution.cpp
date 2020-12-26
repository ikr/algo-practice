#include <bits/stdc++.h>
#include <regex>
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

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

string drop_last(string s) {
    s.erase(prev(cend(s)), cend(s));
    return s;
}

int main() {
    for (string line; getline(cin, line);) {
        const auto parts = split(regex(" \\(contains "), line);
        const auto ingridients = split(regex(" "), parts[0]);
        const auto allergens = split(regex(", "), drop_last(parts[1]));
        cout << ingridients << " " << allergens << '\n';
    }

    return 0;
}
