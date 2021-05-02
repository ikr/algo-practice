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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    string xs;
    cin >> xs;

    deque<char> t;
    bool rev = false;
    int r_num = 0;
    for (const auto x : xs) {
        if (x == 'R') {
            rev = !rev;
            ++r_num;
        } else {
            if (rev) {
                t.push_front(x);
                if (sz(t) > 1 && t[0] == t[1]) {
                    t.pop_front();
                    t.pop_front();
                }
            } else {
                t.push_back(x);
                if (sz(t) > 1 && t.back() == t[sz(t) - 2]) {
                    t.pop_back();
                    t.pop_back();
                }
            }
        }
    }

    string ans(cbegin(t), cend(t));
    if (r_num % 2) reverse(begin(ans), end(ans));

    cout << ans << '\n';
    return 0;
}
