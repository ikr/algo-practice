#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

pii parse_range(const string &src) {
    const auto ab = split("-", src);
    assert(sz(ab) == 2);
    return {stoi(ab[0]), stoi(ab[1])};
}

bool overlap(const pii ab, const pii cd) {
    const auto [a, b] = ab;
    assert(a <= b);
    const auto [c, d] = cd;
    assert(c <= d);
    return !(b < c || d < a);
}

int main() {
    int result{};

    for (string line; getline(cin, line);) {
        const auto pairs = split(",", line);
        assert(sz(pairs) == 2);

        const auto ab = parse_range(pairs[0]);
        const auto cd = parse_range(pairs[1]);
        result += overlap(ab, cd);
    }

    cout << result << '\n';
    return 0;
}
