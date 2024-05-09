#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }
vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(2) << fixed;

    string src;
    cin >> src;

    const auto parts = split(":", src);

    const double im = stoi(parts[1]);
    const double m = (360.0 / 60.0) * im;
    const double h =
        (360.0 / 12.0) * (stoi(parts[0]) % 12) + 30.0 * (im / 60.0);

    auto result = abs(h - m);
    if (result > 180.0) {
        result = 360 - result;
    }
    cout << result << '\n';
    return 0;
}
