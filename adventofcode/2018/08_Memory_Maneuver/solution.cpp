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

struct Node final {
    vector<Node> children;
    vector<int> metadata;
};

Node encode(vector<int>::const_iterator it) {
    const auto num_children = *it;
    ++it;
    vector<Node> children(num_children);

    const auto num_metadata = *it;
    ++it;
    vector<int> metadata(num_metadata);

    return {children, metadata};
}

int main() {
    string input;
    getline(cin, input);

    const auto tokens = split(" ", input);
    vector<int> xs(sz(tokens));
    ranges::transform(tokens, begin(xs), [](const auto &s) { return stoi(s); });

    return 0;
}
