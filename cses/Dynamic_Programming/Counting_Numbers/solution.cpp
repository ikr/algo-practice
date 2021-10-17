#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vi digits(const T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

enum class Tag { LEADING_ZEROS, DIGIT };
struct Pre final {
    Tag tag;
    int value;
    bool capped;
};

Pre lz() { return Pre{Tag::LEADING_ZEROS, -1, false}; }

Pre dig(const int value, const bool capped) {
    return Pre{Tag::DIGIT, value, capped};
}

int numerize(const Pre &pre) {
    if (pre.tag == Tag::LEADING_ZEROS) return -2;
    return pre.capped ? (pre.value * 100) : pre.value;
}

ll sought_nums_up_to(const ll hi) {
    const auto ds = digits(hi);

    function<ll(int, Pre)> recur;
    recur = [&](const int index, const Pre pre) -> ll {
        if (index >= sz(ds)) return 1;

        if (pre.tag == Tag::LEADING_ZEROS) {
            ll ans = recur(index + 1, lz());
            for (int x = 1; x <= 9; ++x) {
                ans += recur(index, dig(x, false));
            }
            return ans;
        } else {
            ll ans{};
            for (int x = 0; x <= (pre.capped ? ds[index] : 9); ++x) {
                if (x == pre.value) continue;
                ans += recur(index + 1, dig(x, pre.capped && (x == ds[index])));
            }
            return ans;
        }
    };

    ll ans = recur(1, lz());
    for (int x = 1; x <= ds[0] - 1; ++x) {
        ans += recur(1, dig(ds[0], false));
    }
    ans += recur(1, dig(ds[0], true));

    return ans;
}

ll sought_nums_in_between(const ll a, const ll b) {
    const auto nums_hi = sought_nums_up_to(b);
    return a ? (nums_hi - sought_nums_up_to(a - 1)) : nums_hi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;

    cout << sought_nums_in_between(a, b) << '\n';
    return 0;
}
