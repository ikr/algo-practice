#include <bits/stdc++.h>
#include <queue>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

struct Op final {
    int i;
    int j;
    int x;
    int y;
};

static constexpr int A_MAX = 1'000'000'000;

vector<Op> operations_sequence(vi xs) {
    vector<Op> ans;
    ans.reserve(sz(xs) / 2);

    for (int i = 1; i < sz(xs);) {
        const int a = min(xs[i - 1], xs[i]);

        priority_queue<int> pq;
        if (i < sz(xs) - 1) pq.push(-xs[i + 1]);
        if (i < sz(xs) - 2) pq.push(-xs[i + 2]);
        const int cd_min = pq.empty() ? 1 : -pq.top();

        xs[i - 1] = a;
        int b = a + 1;
        while (gcd(a, b) != 1 || gcd(b, cd_min) != 1) ++b;

        ans.push_back(Op{i, i + 1, a, b});
        i += 2;
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
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = operations_sequence(move(xs));
        cout << sz(ans) << '\n';

        for (const auto [i, j, x, y] : ans) {
            cout << i << ' ' << j << ' ' << x << ' ' << y << '\n';
        }
    }

    return 0;
}
