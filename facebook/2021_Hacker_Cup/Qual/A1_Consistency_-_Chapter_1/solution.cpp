#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

constexpr bool is_vowel(const char x) {
    switch (x) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return true;
    default:
        return false;
    }
}

constexpr int min_seconds(const char s, const char t) {
    if (s == t) return 0;
    return is_vowel(s) == is_vowel(t) ? 2 : 1;
}

int min_seconds(const string &xs) {
    int ans = INF;

    for (const auto t : string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}) {
        ans = min(ans, transform_reduce(
                           cbegin(xs), cend(xs), 0, plus<int>{},
                           [t](const char s) { return min_seconds(s, t); }));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string xs;
        cin >> xs;

        cout << "Case #" << i << ": " << min_seconds(xs) << '\n';
    }

    return 0;
}
