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
    for (int i = 1; i < sz(ans); ++i) ans[i] = ans[i - 1] * 10;
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
    const auto n = sz(ds);
    assert(n);
    const auto h = ds[0];
    if (n == 1) return h < 4 ? 0 : 1;

    ds.pop_front();
    if (!h) return bad_nums_up_to(ds);

    const auto stt = accumulate(cbegin(BBS) + 1, cbegin(BBS) + n, 0LL);
    if (h == 4) {
        return number<ll>(ds) + 1 + (h - 1) * stt + stt;
    } else if (h < 4) {
        return h * stt + bad_nums_up_to(ds);
    } else {
        assert(h > 4);
        return POWS[n - 1] + (h - 1) * stt + bad_nums_up_to(ds);
    }
}

ll unfour_if_necessary(const ll x) {
    auto s = to_string(x);
    const auto it = s.find('4');
    if (it == s.npos) return x;

    s[it] = '3';
    for (auto i = it + 1; i < s.size(); ++i) s[i] = '9';
    return stoll(s);
}

ll find_ak(const ll k) {
    if (k == 1) return 1;

    ll lo = 1;
    ll hi = INF;

    while (lo + 1 < hi) {
        const auto mid = midpoint<ll>(lo, hi);
        const auto x = mid - bad_nums_up_to(digits(mid));
        if (x == k) return unfour_if_necessary(mid);

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

    int t;
    cin >> t;
    while (t--) {
        ll k;
        cin >> k;
        cout << find_ak(k) << '\n';
    }

    return 0;
}
