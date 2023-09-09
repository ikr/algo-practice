#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> divs;
    for (int i = 1; i <= 9; ++i) {
        if (N % i == 0) divs.push_back(i);
    }

    string ans(N + 1, '-');
    for (int i = 0; i < sz(ans); ++i) {
        for (const auto j : divs) {
            const auto Nj = N / j;
            if (i % Nj == 0) {
                ans[i] = chof('0' + j);
                break;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
