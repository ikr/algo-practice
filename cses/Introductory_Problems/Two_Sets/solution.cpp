#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using usll = unordered_set<ll>;
using pvll = pair<vll, vll>;

pvll partition(const ll n) {
    const ll total = n * (n + 1) / 2;
    if (total % 2) return {{}, {}};
    
    vll xs;
    usll xs_set;
    for (ll i = n, remaining = total / 2; remaining != 0; --i) {
        if (remaining - i >= 0) {
            remaining -= i;
            xs.push_back(i);
            xs_set.insert(i);
        }
    }
    reverse(xs.begin(), xs.end());
    
    vll ys;
    for (ll i = 1; i <= n; ++i) {
        if (xs_set.count(i)) continue;
        ys.push_back(i);
    }
    
    return {xs, ys};
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << xs.size() << '\n';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '\n';
    return os;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    
    const auto [xs, ys] = partition(n);
    if (static_cast<ll>(xs.size() + ys.size()) == n) {
        cout << "YES\n" << xs << ys;
    } else {
        cout << "NO\n";
    }
    
    return 0;
}
