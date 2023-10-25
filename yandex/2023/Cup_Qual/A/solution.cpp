#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int MaxA = 1'000'000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<vector<int>> idx(MaxA + 1);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        idx[a].push_back(i);
    }

    int result{};
    for (int k = 1, i = -1; k <= MaxA; ++k) {
        if (empty(idx[k])) break;
        const auto i_ = idx[k].back();
        if (i_ < i) break;
        i = i_;
        result = k;
    }
    cout << result << '\n';
    return 0;
}
