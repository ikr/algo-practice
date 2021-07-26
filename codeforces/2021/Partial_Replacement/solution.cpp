#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_replacements(string xs, const int k) {
    const int lo = inof(xs.find('*'));
    const int hi = inof(xs.rfind('*'));
    if (lo == hi) return 1;

    xs[hi] = 'x';
    xs[lo] = 'x';

    int ans = 2;
    int curr = lo;

    while (curr + k < hi) {
        int i = curr + k;
        while (xs[i] != '*') --i;
        xs[i] = 'x';
        curr = i;
        ++ans;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s(n, ' ');
        cin >> s;

        const int o1 = min_replacements(s, k);
        reverse(begin(s), end(s));
        const int o2 = min_replacements(s, k);

        cout << min(o1, o2) << '\n';
    }

    return 0;
}
