#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> ladder_up(const map<string, string> &parent,
                         const string &from) {
    vector<string> result;

    auto cur = from;
    while (parent.contains(cur)) {
        result.push_back(parent.at(cur));
        cur = parent.at(cur);
    }

    reverse(begin(result), end(result));
    return result;
}

int main() {
    map<string, string> parent;

    for (string line; getline(cin, line);) {
        const auto sep = line.find(')');
        const auto u = line.substr(0, sep);
        const auto v = line.substr(sep + 1);
        parent.emplace(v, u);
    }

    const auto you = ladder_up(parent, "YOU");
    const auto san = ladder_up(parent, "SAN");

    int k{};
    while (you[k] == san[k]) ++k;
    const auto result = sz(you) - k + sz(san) - k;
    cout << result << '\n';
    return 0;
}
