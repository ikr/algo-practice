#include "json.hpp"
#include <bits/stdc++.h>
using namespace std;

using json = nlohmann::json;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    vector<pair<json, json>> ps;

    for (;;) {
        string line_a;
        getline(cin, line_a);

        string line_b;
        getline(cin, line_b);

        ps.emplace_back(json::parse(line_a), json::parse(line_b));

        if (!getline(cin, line_b)) break;
    }

    cerr << "Read " << sz(ps) << " pairs" << endl;

    return 0;
}
