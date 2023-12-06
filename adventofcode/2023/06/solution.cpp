#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

vector<string> static_re_matches(const string &pattern_str,
                                 const string &input) {
    static const regex pattern{pattern_str};
    smatch m;
    regex_match(input, m, pattern);
    assert(!empty(m));

    vector<string> result(size(m) - 1);
    transform(cbegin(m) + 1, cend(m), begin(result),
              [](const auto &x) { return x.str(); });
    return result;
}

vector<int> parse_ints(const string &src) {
    const auto tokens = split("\\s+", src);
    vector<int> result(sz(tokens));
    ranges::transform(tokens, begin(result),
                      [](const string &s) { return stoi(s); });
    return result;
}

template <typename T> string join(const string &glue, const vector<T> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += to_string(t);
    }

    return ans;
}

static const string LinePattern = R"(^[A-Za-z]+:\s+(\d.+)$)";

ll winning_times_count(const ll t1, const ll D) {
    const auto traveled = [&](const ll t0) -> ll { return t0 * t1 - t0 * t0; };

    ll result{};
    for (ll t0 = 0; t0 <= t1; ++t0) {
        if (traveled(t0) > D) ++result;
    }
    return result;
}

int main() {
    string line;
    getline(cin, line);

    const auto ts = [&]() -> vector<int> {
        const auto parts = static_re_matches(LinePattern, line);
        return parse_ints(parts[0]);
    }();

    getline(cin, line);

    const auto ds = [&]() -> vector<int> {
        const auto parts = static_re_matches(LinePattern, line);
        return parse_ints(parts[0]);
    }();
    assert(sz(ts) == sz(ds));

    const auto t1 = stoll(join("", ts));
    const auto D = stoll(join("", ds));

    cout << winning_times_count(t1, D) << '\n';
    return 0;
}
