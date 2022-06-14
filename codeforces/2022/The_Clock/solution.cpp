#include <cassert>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string format_part(const int x) {
    assert(x < 60);
    const string ans = to_string(x);
    return sz(ans) == 1 ? (string{"0"} + ans) : ans;
}

string format_time(const int t) {
    const auto h = (t / 60) % 24;
    const auto m = t % 60;
    return format_part(h) + ":" + format_part(m);
}

bool is_palin(const string &s) {
    assert(sz(s) == 5);
    return string{s[0], s[1]} == string{s[4], s[3]};
}

int num_palin(const string &s0, const int x) {
    const auto parts = split(":", s0);
    assert(sz(parts) == 2);
    const auto h0 = stoi(parts[0]);
    const auto m0 = stoi(parts[1]);
    const auto t0 = h0 * 60 + m0;

    int result = is_palin(s0) ? 1 : 0;
    int t = t0;

    set<string> seen{s0};

    while (!seen.count(format_time(t + x))) {
        t += x;
        const auto s = format_time(t);
        result += inof(is_palin(s));
        seen.insert(s);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        int x;
        cin >> x;

        cout << num_palin(s, x) << '\n';
    }

    return 0;
}
