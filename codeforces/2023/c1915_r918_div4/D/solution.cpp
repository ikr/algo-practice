#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_v(const char c) { return c == 'a' || c == 'e'; }

string solve(string xs) {
    ranges::reverse(xs);
    string result;

    const auto append_syl = [&](const string &syl) {
        if (!empty(result)) result += ".";
        result += syl;
    };

    for (int i = 0; i < sz(xs);) {
        if (is_v(xs[i])) {
            assert(i + 1 < sz(xs));
            append_syl(string{xs[i], xs[i + 1]});
            i += 2;
        } else {
            assert(i + 2 < sz(xs));
            append_syl(string{xs[i], xs[i + 1], xs[i + 2]});
            i += 3;
        }
    }

    ranges::reverse(result);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);
        cout << solve(std::move(xs)) << '\n';
    }

    return 0;
}
