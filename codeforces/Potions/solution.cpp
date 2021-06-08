#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_drinks(const vi &xs) {
    ll hp = 0;
    int ans = 0;
    priority_queue<int> negs;

    for (const int x : xs) {
        if (x >= 0) {
            ++ans;
            hp += x;
            continue;
        }

        if (x + hp >= 0) {
            negs.push(-x);
            ++ans;
            hp += x;
            continue;
        }

        if (negs.empty()) continue;

        const int y = -negs.top();
        if (y < x) {
            negs.pop();
            negs.push(-x);
            hp -= y;
            hp += x;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_drinks(xs) << '\n';
    return 0;
}
