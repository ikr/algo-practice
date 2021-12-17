#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const string PREFIX{"target area: "};
static const string X_EQ{"x="};
static const string Y_EQ{"y="};

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

pii parse_range(const string &src) {
    const auto parts = split("\\.\\.", src);
    return {stoi(parts[0]), stoi(parts[1])};
}

int possible_velocities_num(const pii rx, const pii ry) {
    const auto [x_lo, x_hi] = rx;
    const auto [y_lo, y_hi] = ry;

    int max_vy = -1;
    set<pii> ans;

    // Direct shot trajectory
    for (int vx0 = 0; vx0 <= x_hi; ++vx0) {
        for (int vy0 = 150; vy0 >= y_lo; --vy0) {
            int vx{vx0};
            int vy{vy0};
            int x{vx};
            int y{vy};
            bool hit{false};

            while (x <= x_hi && y >= y_lo) {
                if (x >= x_lo && y <= y_hi) {
                    hit = true;
                    break;
                }

                if (vx) --vx;
                --vy;

                x += vx;
                y += vy;
            }

            if (hit) {
                max_vy = max(max_vy, vy0);
                ans.emplace(vx0, vy0);
            }
        }
    }
    cerr << "max_vy:" << max_vy << " h_max:" << max_vy * (max_vy + 1) / 2
         << endl;
    return sz(ans);
}

int main() {
    string line;
    getline(cin, line);

    const auto parts = split(", ", line.substr(PREFIX.size()));
    const auto rx = parse_range(parts[0].substr(X_EQ.size()));
    const auto ry = parse_range(parts[1].substr(Y_EQ.size()));

    cout << possible_velocities_num(rx, ry) << '\n';
    return 0;
}
