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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    string letters;
    cin >> letters;

    int q;
    cin >> q;

    string xs(cbegin(letters), cbegin(letters) + n);
    string ys(cbegin(letters) + n, cend(letters));
    assert(sz(xs) == sz(ys));

    bool flipped = false;

    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        --a;
        --b;

        if (t == 2) {
            flipped = !flipped;
            continue;
        }

        assert(t == 1);
        string &left = flipped ? ys : xs;
        string &right = flipped ? xs : ys;

        const int i = min(a, b);
        const int j = max(a, b);

        if (j < n) {
            swap(left[i], left[j]);
            continue;
        }

        if (i >= n) {
            swap(right[i - n], right[j - n]);
            continue;
        }

        assert(i < n && j >= n);
        swap(left[i], right[j - n]);
    }

    const string ans = flipped ? ys + xs : xs + ys;
    cout << ans << '\n';
    return 0;
}
