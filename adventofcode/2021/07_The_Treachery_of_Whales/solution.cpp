#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int main() {
    string in;
    cin >> in;

    const auto src = split(",", in);

    vi xs(sz(src));
    transform(cbegin(src), cend(src), begin(xs),
              [](const auto &x) { return stoi(x); });

    const auto [lo, hi] = minmax_element(cbegin(xs), cend(xs));

    int ans{INT_MAX};

    for (int m = *lo; m <= *hi; ++m) {
        int candidate{};

        for (int i = 0; i < sz(xs); ++i) {
            const int k = abs(xs[i] - m);
            candidate += k * (k + 1) / 2;
        }

        ans = min(ans, candidate);
    }

    cout << ans << '\n';
    return 0;
}
