#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const multiset<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_end_sum(const vi &xs) {
    multiset<ll> ev;
    multiset<ll> od;

    for (const auto x : xs) {
        if (x % 2) {
            od.insert(x);
        } else {
            ev.insert(x);
        }
    }

    const auto final_result = [&]() -> ll {
        return accumulate(cbegin(ev), cend(ev), 0LL) +
               accumulate(cbegin(od), cend(od), 0LL);
    };

    if (ev.empty()) return final_result();

    if (sz(ev) == 1 &&
        (od.empty() || 2LL * (*crbegin(od)) + (*cbegin(ev)) / 2LL <=
                           *cbegin(ev) + *crbegin(od))) {
        return final_result();
    }

    const auto maybe_mul_odd = [&]() {
        if (!ev.empty() && !od.empty() &&
            2LL * (*crbegin(od)) + (*cbegin(ev)) / 2LL >
                *cbegin(ev) + *crbegin(od)) {
            const auto ai = *cbegin(ev);
            ev.erase(cbegin(ev));

            const auto hi = *crbegin(od);
            od.erase(prev(cend(od)));
            ev.insert(hi * 2LL);

            const auto ai_ = ai / 2LL;
            if (ai_ % 2LL) {
                od.insert(ai_);
            } else {
                ev.insert(ai_);
            }
        }
    };

    maybe_mul_odd();

    while (sz(ev) > 1) {
        const auto ai = *cbegin(ev);
        ev.erase(cbegin(ev));

        if (od.empty() || *crbegin(ev) > *crbegin(od)) {
            const auto hi = *crbegin(ev);
            ev.erase(prev(cend(ev)));
            ev.insert(hi * 2LL);
        } else {
            const auto hi = *crbegin(od);
            od.erase(prev(cend(od)));
            ev.insert(hi * 2LL);
        }

        const auto ai_ = ai / 2LL;
        if (ai_ % 2LL) {
            od.insert(ai_);
        } else {
            ev.insert(ai_);
        }

        maybe_mul_odd();
    }

    return final_result();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_end_sum(xs) << '\n';
    }

    return 0;
}
