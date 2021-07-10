#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o) {
        os << "nullopt";
    } else {
        os << *o;
    }
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi sinks(const vvi &rg) {
    vi ans;
    for (int i = 0; i < sz(rg); ++i) {
        if (rg[i].empty()) ans.push_back(i);
    }
    return ans;
}

vector<optional<bool>> can_win(const vvi &rg) {
    const int n = sz(rg);
    vector<optional<bool>> ans(n, optional<bool>{nullopt});

    const auto s = sinks(rg);

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    map<string, vi> by_pref;
    map<string, vi> by_suff;
    vector<string> ss(n);

    for (int i = 0; i < n; ++i) {
        cin >> ss[i];
        by_pref[ss[i].substr(0, 3)].push_back(i);
        by_suff[ss[i].substr(sz(ss[i]) - 3, 3)].push_back(i);
    }

    vvi rg(n);
    for (int i = 0; i < n; ++i) {
        for (const int j : by_suff[ss[i].substr(0, 3)]) {
            rg[i].push_back(j);
        }
    }

    const auto ans = can_win(rg);
    for (const auto o : ans) {
        if (!o) {
            cout << "Draw\n";
            continue;
        }

        cout << (*o ? "Takahashi" : "Aoki") << '\n';
    }
    return 0;
}
