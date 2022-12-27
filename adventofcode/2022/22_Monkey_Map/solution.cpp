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

vector<string> tokenize_command_source(const string &src) {
    const regex pattern("[0-9]+|L|R");
    vector<string> result;
    copy(sregex_token_iterator(cbegin(src), cend(src), pattern),
         sregex_token_iterator(), back_inserter(result));
    return result;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (line == "") break;
        grid.push_back(line);
    }

    for (const auto &row : grid) cerr << row << endl;

    string command_source;
    cin >> command_source;

    cerr << tokenize_command_source(command_source) << endl;
    return 0;
}
