#include <bits/stdc++.h>
using namespace std;

static const set<char> Vowels{'a', 'e', 'i', 'o', 'u'};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    string ans;
    for (const auto &x : xs) {
        if (Vowels.count(x)) continue;
        ans += x;
    }

    cout << ans << '\n';
    return 0;
}
