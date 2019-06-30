#include <bits/stdc++.h>

using namespace std;

int main() {
    int queries_count;
    cin >> queries_count;

    for (int i = 0; i != queries_count; ++i) {
        int n;
        int s;
        int t;
        cin >> n >> s >> t;

        const int doubles = s + t - n;
        const int ans = doubles ? max(s, t) - doubles + 1 : max(s, t) + 1;
        cout << ans << '\n';
    }
}
