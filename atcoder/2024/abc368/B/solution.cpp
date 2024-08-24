#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    int result{};

    while (count_if(cbegin(xs), cend(xs), [](const int x) { return x > 0; }) >
           1) {
        sort(rbegin(xs), rend(xs));
        --xs[0];
        --xs[1];
        ++result;
    }

    cout << result << '\n';
    return 0;
}
