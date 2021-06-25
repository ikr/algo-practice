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

string outcome(const vi &xs) {
    priority_queue<int> a;
    priority_queue<int> b;

    for (const auto x : xs) {
        if (x % 2) {
            b.push(x);
        } else {
            a.push(x);
        }
    }

    ll sa = 0;
    ll sb = 0;
    bool my_turn = true;

    while (!a.empty() || !b.empty()) {
        if (my_turn) {
            if (!a.empty() && !b.empty()) {
                if (a.top() >= b.top()) {
                    sa += a.top();
                    a.pop();
                } else {
                    b.pop();
                }
            } else if (!a.empty()) {
                sa += a.top();
                a.pop();
            } else if (!b.empty()) {
                b.pop();
            }
        } else {
            if (!a.empty() && !b.empty()) {
                if (b.top() >= a.top()) {
                    sb += b.top();
                    b.pop();
                } else {
                    a.pop();
                }
            } else if (!b.empty()) {
                sb += b.top();
                b.pop();
            } else if (!a.empty()) {
                a.pop();
            }
        }

        my_turn = !my_turn;
    }

    if (sa == sb) return "Tie";
    return sa > sb ? "Win" : "Lose";
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

        cout << outcome(xs) << '\n';
    }

    return 0;
}
