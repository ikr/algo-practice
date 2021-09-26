#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi digits_reversed(const ll x) {
    if (!x) return {0};

    vi ans;
    ll r = x;

    while (r) {
        ans.push_back(inof(r % 10LL));
        r /= 10LL;
    }

    return ans;
}

vi digits(const ll x) {
    auto ans = digits_reversed(x);
    reverse(begin(ans), end(ans));
    return ans;
}

struct LeadingZeros final {};
struct Nothing final {};
struct Digit final {
    int value;
};
using Pre = variant<LeadingZeros, Nothing, Digit>;
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// The recursion state
struct State final {
    int digits_count;
    Pre pre;
    bool capped;
};

int numerize(const Pre &pre) {
    return visit(overloaded{
                     [](const LeadingZeros it) -> int { return -2; },
                     [](const Nothing it) -> int { return -1; },
                     [](const Digit it) -> int { return it.value; },
                 },
                 pre);
}

bool operator<(const State &lhs, const State &rhs) {
    const array<int, 3> a{lhs.digits_count, numerize(lhs.pre), lhs.capped};
    const array<int, 3> b{rhs.digits_count, numerize(rhs.pre), rhs.capped};
    return a < b;
}

ll sought_nums_up_to(const ll hi) {
    const auto ds = digits(hi);

    map<State, ll> memo;
    function<ll(State)> recur;
    recur = [&](const State &s) -> ll {
        const auto it = memo.find(s);
        if (it != cend(memo)) return it->second;

        const int i = sz(ds) - s.digits_count;

        for (int d = 0; d <= 9; ++d) {
            if (s.capped && d == ds[i]) break;
        }

        ll ans = 0;
        const pii ab = visit(overloaded{
                                 [](const LeadingZeros _) -> pii {
                                     return {0, 9};
                                 },
                                 [&](const Nothing _) -> pii {
                                     return {0, ds[i]};
                                 },
                                 [](const Digit x) -> pii { return {}; },
                             },
                             s.pre);

        memo[s] = ans;
        return ans;
    };

    return recur({sz(ds), Nothing{}, true});
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
