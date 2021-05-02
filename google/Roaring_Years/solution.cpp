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

vector<int> digits_reversed(long long n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % 10LL));
        n /= 10;
    }

    return ans;
}

vector<int> digits(long long n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

void remove_leading_zeros(vector<int> &ds) {
    for (auto it = ds.begin(); it != ds.end();) {
        if (*it != 0) break;
        it = ds.erase(it);
    }
}

long long number(const vector<int> &ds) {
    if (ds.empty()) return 0;

    long long ans = 0;
    long long mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= 10LL;
    }
    return ans;
}

vi subvector(const vi &xs, const int i, const int l) {
    vi ans(cbegin(xs) + i, cbegin(xs) + i + l);
    return ans;
}

bool is_roaring(const int step, const int x) {
    const auto ds = digits(x);
    const auto head = subvector(ds, 0, step);

    const auto ns = digits(number(head) + 1);
    if (step + sz(ns) < sz(ds) && subvector(ds, step, sz(ns)) == ns) {
    }

    return false;
}

int solve(const int x) {
    const auto ds = digits(x);

    for (int step = 1; step <= sz(ds); ++step) {
        const vi tops(step, 9);
        vi os = subvector(ds, 0, step);
        auto pre = os;

        for (int i = step; i + step <= sz(ds); i += step) {
            const auto curr = subvector(ds, i, step);
        }
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int x;
        cin >> x;

        cout << "Case #" << i << ": " << solve(x) << '\n';
    }

    return 0;
}
