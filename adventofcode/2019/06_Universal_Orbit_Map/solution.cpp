#include <bits/stdc++.h>
using namespace std;

using Graph = map<string, string>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> toposort(const vector<string> &vertices, const Graph &follows) {
    vector<string> result;
    set<string> done;

    const auto recur = [&](const auto self, const string &u) -> void {
        done.insert(u);

        if (follows.contains(u) && !done.contains(follows.at(u))) {
            self(self, follows.at(u));
        }

        result.push_back(u);
    };

    for (int i = 0; i < sz(vertices); ++i) {
        if (done.contains(vertices[i])) continue;
        recur(recur, vertices[i]);
    }

    return result;
}

int main() {
    Graph follows;
    set<string> vertices;

    for (string line; getline(cin, line);) {
        const auto sep = line.find(')');
        const auto u = line.substr(0, sep);
        const auto v = line.substr(sep + 1);
        follows.emplace(v, u);
        vertices.insert(u);
        vertices.insert(v);
    }

    const auto order =
        toposort(vector(cbegin(vertices), cend(vertices)), follows);

    int result{};
    map<string, int> orbits;

    for (const auto &u : order) {
        if (follows.contains(u)) {
            const auto v = follows.at(u);
            orbits[u] = orbits[v] + 1;
            result += orbits.at(u);
        }
    }

    cout << result << '\n';
    return 0;
}
