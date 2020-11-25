#include <bits/stdc++.h>
#include <string>
using namespace std;
using ll = long long;

bool solve(const ll a, const ll s) {
    const ll b = s - a;

    string as = to_string(a);
    string bs = to_string(b);

    sort(begin(as), end(as));
    sort(begin(bs), end(bs));

    return as == bs;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll a, s;
    cin >> a >> s;

    cout << (solve(a, s) ? "YES\n" : "NO\n");

    return 0;
}
