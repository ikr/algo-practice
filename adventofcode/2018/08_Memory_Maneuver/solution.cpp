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

Node encode(vector<int>::const_iterator &it) {
    vector<Node> children(*it++);
    vector<int> metadata(*it++);

    for (auto &child : children) child = encode(it);
    for (auto &x : metadata) x = *it++;

    return {children, metadata};
}

int main() {
    string input;
    getline(cin, input);

    const auto tokens = split(" ", input);
    vector<int> xs(sz(tokens));
    ranges::transform(tokens, begin(xs), [](const auto &s) { return stoi(s); });

    auto it = cbegin(xs);
    const auto root = encode(it);
    assert(it == cend(xs));

    const auto value_of_node = [&](const auto self, const Node &node) -> int {
        if (empty(node.children)) {
            return accumulate(cbegin(node.metadata), cend(node.metadata), 0);
        }

        const auto nc = sz(node.children);

        return accumulate(cbegin(node.metadata), cend(node.metadata), 0,
                          [&](const int acc, const int p) {
                              const auto i = p - 1;
                              return (0 <= i && i < nc)
                                         ? (acc + self(self, node.children[i]))
                                         : acc;
                          });
    };

    cout << value_of_node(value_of_node, root) << '\n';
    return 0;
}
