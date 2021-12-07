#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    string in;
    cin >> in;

    const auto src = split(",", in);

    vi xs(sz(src));
    transform(cbegin(src), cend(src), begin(xs),
              [](const auto &x) { return stoi(x); });

    sort(begin(xs), end(xs));
    const auto mi = div_ceil(sz(xs), 2);

    int ans{};
    for (int i = 0; i < sz(xs); ++i) {
        ans += abs(xs[i] - xs[mi]);
    }

    cout << ans << '\n';
    return 0;
}
