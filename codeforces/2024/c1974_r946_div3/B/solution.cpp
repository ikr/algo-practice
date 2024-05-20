#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string recover_src(const string &dst) {
    const auto n = sz(dst);
    const set<char> alpha_set(cbegin(dst), cend(dst));
    const vector<char> alpha(cbegin(alpha_set), cend(alpha_set));
    const auto m = sz(alpha);

    string src(n, ' ');
    for (int i = 0; i < n; ++i) {
        const auto j =
            inof(find(cbegin(alpha), cend(alpha), dst[i]) - cbegin(alpha));
        const auto j_ = m - 1 - j;
        src[i] = alpha[j_];
    }
    return src;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string dst;
        cin >> dst;
        assert(sz(dst) == n);

        cout << recover_src(dst) << '\n';
    }

    return 0;
}
