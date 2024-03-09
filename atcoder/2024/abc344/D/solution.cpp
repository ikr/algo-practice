#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int Inf = 1'000'000'000;

bool match_from_t(const string &T, const int t, const string &s) {
    if (t + sz(s) > sz(T)) return false;

    for (int i = 0; i < sz(s); ++i) {
        if (T[t + i] != s[i]) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string T;
    cin >> T;

    int N;
    cin >> N;

    vector<vector<string>> S(N);
    for (auto &row : S) {
        int a;
        cin >> a;

        for (int i = 0; i < a; ++i) {
            string s;
            cin >> s;
            row.push_back(s);
        }
    }

    // cerr << S << endl;

    vector<vector<int>> dp(sz(T) + 1, vector(sz(S) + 1, Inf));

    for (int i = 0; i < sz(S); ++i) {
        for (const auto &s : S[i]) {
            if (T.starts_with(s)) dp[sz(s)][i + 1] = 1;
        }
    }

    // cerr << dp << endl;

    for (int t = 1; t < sz(T); ++t) {
        for (int i = 1; i < sz(S); ++i) {
            for (const auto &s : S[i]) {
                dp[t][i + 1] = min(dp[t][i + 1], dp[t][i]);

                if (dp[t][i] != Inf && match_from_t(T, t, s)) {
                    dp[t + sz(s)][i + 1] =
                        min(dp[t + sz(s)][i + 1], dp[t][i] + 1);
                }
            }
        }
    }

    // cerr << dp << endl;

    const auto ans = *min_element(cbegin(dp.back()), cend(dp.back()));
    if (ans == Inf) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
    return 0;
}
