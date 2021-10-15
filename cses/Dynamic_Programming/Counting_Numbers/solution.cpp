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

struct LeadingZeros final {};
struct Digit final {
    int value;
    bool capped;
};
using Pre = variant<LeadingZeros, Digit>;
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int numerize(const Pre &pre) {
    return visit(overloaded{
                     [](__attribute__((unused)) const LeadingZeros it) -> int {
                         return -2;
                     },
                     [](const Digit it) -> int {
                         return it.capped ? (it.value * 100) : it.value;
                     },
                 },
                 pre);
}

ll sought_nums_up_to(const ll hi) {
    const auto ds = digits(hi);

    function<ll(int, Pre)> recur;
    recur = [&](const int index, const Pre pre) -> ll {
        if (index >= sz(ds)) return 1;

        return visit(
            overloaded{
                [&](__attribute__((unused)) const LeadingZeros it) -> ll {
                    ll ans = recur(index + 1, LeadingZeros{});
                    for (int x = 1; x <= 9; ++x) {
                        ans += recur(index, Digit{x, false});
                    }
                    return ans;
                },
                [&](const Digit it) -> ll {
                    ll ans{};
                    for (int x = 0; x <= (it.capped ? ds[index] : 9); ++x) {
                        if (x == it.value) continue;
                        ans += recur(index + 1,
                                     Digit{x, it.capped && (x == ds[index])});
                    }
                    return ans;
                },
            },
            pre);
    };

    ll ans = recur(1, LeadingZeros{});
    for (int x = 1; x <= ds[0] - 1; ++x) {
        ans += recur(1, Digit{ds[0], false});
    }
    ans += recur(1, Digit{ds[0], true});

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
