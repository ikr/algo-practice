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

    vector<string> names(n);
    vector<int> ages(n);
    for (int i = 0; i < n; ++i) {
        cin >> names[i] >> ages[i];
    }

    const auto i0 = inof(min_element(cbegin(ages), cend(ages)) - cbegin(ages));
    rotate(begin(names), begin(names) + i0, end(names));

    for (const auto &name : names) {
        cout << name << '\n';
    }

    return 0;
}
