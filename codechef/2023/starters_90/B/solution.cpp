#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_pali(const array<int, 26> &freq) {
    return all_of(cbegin(freq), cend(freq),
                  [](const int f) { return f % 2 == 0; }) ||
           inof(count_if(cbegin(freq), cend(freq),
                         [](const int f) { return f % 2 == 1; })) == 1;
}

int min_ops(const string &xs) {
    array<int, 26> freq{};
    for (const auto &x : xs) ++freq[inof(x) - inof('a')];

    if (!is_pali(freq)) return 0;

    const auto groups = inof(
        count_if(cbegin(freq), cend(freq), [](const int f) { return f != 0; }));
    if (groups == 1) {
        const auto has_odd = any_of(cbegin(freq), cend(freq),
                                    [](const int f) { return f % 2 == 1; });
        return has_odd ? 2 : 1;
    } else {
        return 1;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
