#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int integer_value(const string &x) { return stoi(x); }

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<int> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs), integer_value);

    return 0;
}
