#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> indices_by_value(const int M, const vector<int> &xs) {
    vector<vector<int>> ans(M);
    for (int i = 0; i < sz(xs); ++i) ans[xs[i]].push_back(i);
    return ans;
}

string shifted(const int M, const string &s, const vector<int> &xs) {
    const auto idx = indices_by_value(M, xs);

    string ans(sz(s), ' ');
    for (const auto &ii : idx) {
        if (ii.empty()) continue;

        if (sz(ii) == 1) {
            ans[ii[0]] = s[ii[0]];
            continue;
        }

        for (int j = 1; j < sz(ii); ++j) {
            ans[ii[j]] = s[ii[j - 1]];
        }

        ans[ii[0]] = s[ii.back()];
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    string s;
    cin >> s;

    vector<int> xs(N);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    cout << shifted(M, s, xs) << '\n';
    return 0;
}
