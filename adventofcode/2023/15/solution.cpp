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

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int hash_algo(const string &xs) {
    int result{};
    for (const auto x : xs) {
        result += inof(x);
        result *= 17;
        result %= 256;
    }
    return result;
}

int main() {
    string line;
    getline(cin, line);
    const auto tokens = split(",", line);
    cerr << tokens << endl;

    vector<int> hashes(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(hashes), hash_algo);
    cerr << hashes << endl;

    cout << accumulate(cbegin(hashes), cend(hashes), 0) << endl;
    return 0;
}
