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

bool is_multientrant(const string &u) {
    return all_of(cbegin(u), cend(u),
                  [](const char x) -> bool { return isupper(x); });
}

int paths_num(const multimap<string, string> &g) {
    int ans{};

    function<void(set<string>, string)> recur;
    recur = [&](set<string> nogo, const string &u) {
        if (u == "end") {
            ++ans;
            return;
        }

        if (!is_multientrant(u)) nogo.insert(u);

        const auto [first, last] = g.equal_range(u);
        for (auto it = first; it != last; ++it) {
            const auto v = it->second;
            if (nogo.count(v)) continue;
            recur(nogo, v);
        }
    };

    recur({}, "start");
    return ans;
}

int main() {
    multimap<string, string> g;

    for (string line; getline(cin, line);) {
        const auto parts = split("-", line);
        assert(sz(parts) == 2);
        const auto u = parts[0];
        const auto v = parts[1];

        g.emplace(u, v);
        g.emplace(v, u);
    }

    cout << paths_num(g) << '\n';
    return 0;
}
