#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    vector<int> fs(26, 0);
    for (const auto x : xs) ++fs[x - 'a'];

    const auto it = max_element(cbegin(fs), cend(fs));
    const auto ans = static_cast<char>(inof(it - cbegin(fs)) + 'a');
    cout << ans << '\n';
    return 0;
}
