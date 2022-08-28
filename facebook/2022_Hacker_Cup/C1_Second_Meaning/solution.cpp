#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char flip(const char x) { return x == '-' ? '.' : '-'; }

vector<string> complementing_codewords(const int N, const string &C1) {
    vector<string> result;
    result.reserve(N - 1);

    string cw = C1;
    for (int i = 2; i <= N; ++i) {
        cw.back() = flip(cw.back());
        cw += '.';
        result.push_back(cw);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        string C1;
        cin >> C1;

        cout << "Case #" << i << ":\n";
        for (const auto &cw : complementing_codewords(N, C1)) {
            cout << cw << '\n';
        }
    }

    return 0;
}
