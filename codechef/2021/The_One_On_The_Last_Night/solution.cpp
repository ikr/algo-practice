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

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }

    return ans;
}

int max_value(const int n, int k) {
    int nines{};

    priority_queue<int, vi, greater<int>> ds;
    for (const int d : digits_reversed(n)) {
        if (d == 9) {
            ++nines;
        } else {
            ds.push(d);
        }
    }

    while (k > 0 && !ds.empty()) {
        const int d = ds.top();
        ds.pop();

        if (d + 1 == 9) {
            ++nines;
        } else {
            ds.push(d + 1);
        }

        --k;
    }

    int ans = 1;
    for (int i = 1; i <= nines; ++i) {
        ans *= 9;
    }

    while (!ds.empty()) {
        const int d = ds.top();
        ds.pop();
        ans *= d;
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

        cout << max_value(n, k) << '\n';
    }

    return 0;
}
