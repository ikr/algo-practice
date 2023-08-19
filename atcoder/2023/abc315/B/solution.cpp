#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int M;
    cin >> M;

    vector<int> xs(M);
    for (auto &x : xs) cin >> x;

    const auto total = accumulate(cbegin(xs), cend(xs), 0);

    vector<int> ss(M);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    int i{};
    while (ss[i] < total / 2 + 1) ++i;

    int s = i ? ss[i - 1] : 0;
    const int a = i + 1;
    const auto b = total / 2 + 1 - s;
    cout << a << ' ' << b << '\n';
    return 0;
}
