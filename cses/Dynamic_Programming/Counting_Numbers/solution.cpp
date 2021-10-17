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

constexpr int numerize(const Pre &pre) {
    if (pre.tag == Tag::LEADING_ZEROS) return -2;
    return pre.capped ? (pre.value * 11) : pre.value;
}

struct State final {
    int index;
    Pre pre;
};

bool operator<(const State &lhs, const State &rhs) {
    return pii{lhs.index, numerize(lhs.pre)} <
           pii{rhs.index, numerize(rhs.pre)};
}

ll sought_nums_up_to(const ll hi) {
    if (!hi) return 1;
    const auto ds = digits(hi);
    if (sz(ds) == 1) return hi + 1;

    map<State, ll> memo;
    function<ll(int, Pre)> recur;
    recur = [&](const int index, const Pre &pre) -> ll {
        const State key{index, pre};
        const auto known = memo.find(key);
        if (known != cend(memo)) return known->second;

        return memo[key] = [&]() -> ll {
            if (index >= sz(ds)) return 0;

            if (index == sz(ds) - 1) {
                if (pre.tag == Tag::LEADING_ZEROS) {
                    return 10;
                }

                ll ans{};
                const auto upto = (pre.capped ? ds.back() : 9);
                for (int x = 0; x <= upto; ++x) {
                    if (x == pre.value) continue;
                    ++ans;
                }
                return ans;
            }

            if (pre.tag == Tag::LEADING_ZEROS) {
                ll ans = recur(index + 1, lz());
                for (int x = 1; x <= 9; ++x) {
                    ans += recur(index + 1, dig(x, false));
                }
                return ans;
            }

            {
                ll ans{};
                for (int x = 0; x <= (pre.capped ? ds[index] : 9); ++x) {
                    if (x == pre.value) continue;
                    ans += recur(index + 1,
                                 dig(x, pre.capped && (x == ds[index])));
                }
                return ans;
            }
        }();
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
