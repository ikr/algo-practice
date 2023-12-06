#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

static const string LinePattern = R"(^[A-Za-z]+:\s+(\d.+)$)";

int winning_times_count(const int t1, const int D) {
    const auto traveled = [&](const int t0) -> int {
        return t0 * t1 - t0 * t0;
    };

    int result{};
    for (int t0 = 0; t0 <= t1; ++t0) {
        cerr << "t1:" << t1 << " D:" << D << " t0:" << t0
             << " d:" << traveled(t0) << endl;
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

    int result{1};
    for (int i = 0; i < sz(ts); ++i) {
        cerr << winning_times_count(ts[i], ds[i]) << endl;
        result *= winning_times_count(ts[i], ds[i]);
    }
    cout << result << '\n';
    return 0;
}
