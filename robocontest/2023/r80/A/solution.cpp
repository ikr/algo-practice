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

template <typename T> string join(const string &glue, const vector<T> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += t;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    getline(cin, s);

    auto xs = split(" ", s);
    transform(cbegin(xs), cend(xs), begin(xs), [](const string &x) {
        if (sz(x) <= 10) return x;
        const auto l = sz(x) / 2;
        return x.substr(0, l) + "-" + x.substr(l);
    });

    const auto result = join("-", xs);
    cout << result << '\n';
    return 0;
}
