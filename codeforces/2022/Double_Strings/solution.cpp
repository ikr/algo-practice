#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string presentation_code(const vector<string> &xss) {
    const set<string> idx(cbegin(xss), cend(xss));

    const auto n = sz(xss);
    string result(n, '0');

    for (int i = 0; i < n; ++i) {
        const auto xs = xss[i];
        for (int j = 0; j < sz(xs) - 1; ++j) {
            const auto a = xs.substr(0, j + 1);
            const auto b = xs.substr(j + 1);

            if (idx.count(a) && idx.count(b)) {
                result[i] = '1';
            }
        }
    }

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

        vector<string> xss(n);
        for (auto &xs : xss) cin >> xs;

        cout << presentation_code(xss) << '\n';
    }

    return 0;
}
