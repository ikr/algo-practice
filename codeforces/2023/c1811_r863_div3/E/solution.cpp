#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll INF = 1'000'000'000'000'000'000LL;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> deque<int> digits_reversed(T n) {
    deque<int> ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> deque<int> digits(T n) {
    auto ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

template <typename T> T number(const deque<int> &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

static const auto POWS = []() {
    array<ll, 18> ans{};
    ans[0] = 1;

    for (int i = 1; i < sz(ans); ++i) {
        ans[i] = ans[i - 1] * 10;
    }

    return ans;
}();

static const auto BBS = []() {
    array<ll, 18> ans{};
    ans[1] = 1;
    ll m = 10;

    for (int i = 2; i < sz(ans); ++i) {
        ans[i] = m + 8 * accumulate(cbegin(ans), cbegin(ans) + i, 0LL);
        m *= 10;
    }

    return ans;
}();

ll bad_nums_up_to(deque<int> ds) {
    if (sz(ds) == 1) return ds[0] < 4 ? 0 : 1;

    const auto sub = BBS[sz(ds) - 1];
    const auto x = ds[0] - 1;
    ll ans = x < 4 ? (x * sub) : ((x - 1) * sub + POWS[sz(ds) - 1]);

    ds.pop_front();
    if (ds[0] == 4) {
        ans += number<ll>(ds) + 1;
    } else {
        ans += bad_nums_up_to(ds);
    }

    return ans;
}

ll find_ak(const ll k) {
    if (k == 1) return 1;

    ll lo = 1;
    ll hi = INF;

    while (lo + 1 < hi) {
        cerr << "lo:" << lo << " hi:" << hi << endl;
        const auto mid = midpoint<ll>(lo, hi);
        const auto x = mid - bad_nums_up_to(digits(mid));
        if (x == k) return mid;

        if (x < k) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    assert("/o\\" && false);
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const int K = 999;
    int exp = 0;
    for (int i = 1; i <= K; ++i) {
        const auto ds = to_string(i);
        exp += ds.find('4') != ds.npos;

        if (ds.find('4') != ds.npos) {
            cerr << ds << endl;
        }
    }
    const auto act = bad_nums_up_to(digits(K));
    cerr << "exp:" << exp << " act:" << act
         << " BBS:" << (BBS[1] + BBS[2] + BBS[3]) << endl;
    return 0;

    int t;
    cin >> t;
    while (t--) {
        ll k;
        cin >> k;

        cout << find_ak(k) << '\n';
    }

    return 0;
}
