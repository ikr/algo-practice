#include <bits/stdc++.h>
using namespace std;

vector<string> tokenize(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

int wait_time(const int t, const int bus) {
    const int r = t % bus;
    return r ? bus - r : 0;
}

int solve(const int t, const vector<string> &tt) {
    int best_wait_t = 1e9;
    int best_bus = -1;

    for (const auto b : tt) {
        if (b == "x") continue;

        const int id = stoi(b);
        const int wt = wait_time(t, id);
        if (wt < best_wait_t) {
            best_wait_t = wt;
            best_bus = id;
        }
    }

    return best_bus * best_wait_t;
}

int main() {
    int t;
    cin >> t;
    string s;
    cin >> s;

    cout << solve(t, tokenize(regex(","), s)) << '\n';

    return 0;
}
