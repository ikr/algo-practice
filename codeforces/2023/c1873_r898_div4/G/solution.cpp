#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_coins(const string &xs) {
    if (sz(xs) == 1) return 0;

    vector<int> ch(sz(xs), 0);
    vector<int> id(sz(xs), 0);

    const string p0{xs[0], xs[1]};
    if (p0 == "AB" || p0 == "BA") ch[1] = 1;

    for (int i = 2; i < sz(xs); ++i) {
        const string pre{xs[i - 2], xs[i - 1]};
        const string cur{xs[i - 1], xs[i]};

        if (cur == "AB") {
            ch[i] = id[i - 1] + 1;
            id[i] = max(ch[i - 1], id[i - 1]);
        } else if (cur == "BA") {
            if (pre == "AB") {
                ch[i] = max(id[i - 1] + 1, ch[i - 1] + 1);
            } else {
                ch[i] = id[i - 1] + 1;
            }
            id[i] = max(ch[i - 1], id[i - 1]);
        } else {
            if (pre == "AB" && cur[1] == 'A') ch[i] = ch[i - 1] + 1;
            id[i] = max(ch[i - 1], id[i - 1]);
        }
    }

    return max(ch.back(), id.back());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << max_coins(xs) << '\n';
    }

    return 0;
}
