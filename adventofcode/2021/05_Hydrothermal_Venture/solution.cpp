#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pii parse_pair(const string &src) {
    const auto xs = split(",", src);
    return {stoi(xs[0]), stoi(xs[1])};
}

int main() {
    map<pii, int> freqs;

    for (string line; getline(cin, line);) {
        const auto coord_pairs_src = split(" -> ", line);
        const auto [x1, y1] = parse_pair(coord_pairs_src[0]);
        const auto [x2, y2] = parse_pair(coord_pairs_src[1]);

        if (x1 == x2) {
            for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
                ++freqs[pii{x1, y}];
            }
        } else if (y1 == y2) {
            for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
                ++freqs[pii{x, y1}];
            }
        }
    }

    int ans{};

    for (const auto [_, f] : freqs) {
        if (f > 1) ++ans;
    }

    cout << ans << '\n';
    return 0;
}
