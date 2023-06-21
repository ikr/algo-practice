#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        map<string, int> freq;

        for (int i = 0; i < n; ++i) {
            string x;
            cin >> x;
            ++freq[x];
        }

        const auto ans = max(freq["O"] + freq["A"] + freq["AB"],
                             freq["O"] + freq["B"] + freq["AB"]);
        cout << ans << '\n';
    }

    return 0;
}
