#include <cassert>
#include <deque>
#include <iostream>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const deque<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    deque<pair<ll, ll>> cyl;

    const auto push_balls = [&](const ll x, const ll c) -> void {
        if (!cyl.empty() && cyl.back().first == x) {
            cyl.back().second += c;
        } else {
            cyl.emplace_back(x, c);
        }
    };

    const auto pop_balls = [&](const ll c) -> ll {
        ll result{};
        ll curr = 0;

        while (curr < c) {
            const auto [fx, fc] = cyl.front();
            cyl.pop_front();

            if (fc <= c - curr) {
                curr += fc;
                result += fc * fx;
            } else {
                const auto delta = c - curr;
                assert(delta < fc);

                curr += delta;
                assert(c == curr);
                result += delta * fx;
                cyl.emplace_front(fx, fc - delta);
            }
        }

        return result;
    };

    int cas;
    cin >> cas;
    while (cas--) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            ll x, c;
            cin >> x >> c;
            push_balls(x, c);
        } else {
            assert(cmd == 2);
            ll c;
            cin >> c;
            cout << pop_balls(c) << '\n';
        }
        // cerr << "cyl: " << cyl << endl;
    }

    return 0;
}
