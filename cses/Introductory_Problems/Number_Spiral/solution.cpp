#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll diag_value(const ll i) {
    return i * i - i + 1;
}

constexpr ll num_at(const ll r, const ll c) {
    const ll i = max(r, c);
    const ll d = diag_value(i);
    
    if (r <= c) {
        return (i % 2) ? d + c - r : d - c + r;
    } else {
        return (i % 2) ? d - r + c : d + r - c;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    
    while (t--) {
        ll r, c;
        cin >> r >> c;
        cout << num_at(r, c) << '\n';
    }

    return 0;
}
