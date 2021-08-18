#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int SZ = inof('z') - inof('a') + 1;

string removal_seq(const string &t) {
    vector<bool> seen(SZ, false);
    string ans;

    for (auto it = crbegin(t); it != crend(t); ++it) {
        const int i = inof(*it) - inof('a');

        if (!seen[i]) {
            seen[i] = true;
            ans.push_back(*it);
        }
    }

    reverse(begin(ans), end(ans));
    return ans;
}

pair<string, string> s_and_removal_seq(const string &t) {
    return {"?", removal_seq(t)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int T;
    cin >> T;
    while (T--) {
        string t;
        cin >> t;

        const auto [s, xs] = s_and_removal_seq(t);
        cout << s << ' ' << xs << '\n';
    }

    return 0;
}
