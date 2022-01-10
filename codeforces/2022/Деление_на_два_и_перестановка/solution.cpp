#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

priority_queue<int> x_yield(const int n, int x) {
    priority_queue<int> ans;

    while (x > 0) {
        if (x <= n) ans.push(x);
        x /= 2;
    }

    return ans;
}

bool is_possible(const vi &xs) {
    const auto n = sz(xs);
    vector<priority_queue<int>> ys(n);
    transform(cbegin(xs), cend(xs), begin(ys),
              [n](const auto x) { return x_yield(n, x); });

    auto sort_ys = [&]() {
        ys.erase(remove_if(begin(ys), end(ys),
                           [](const auto &y) { return y.empty(); }),
                 end(ys));

        sort(begin(ys), end(ys), [](const auto &lhs, const auto &rhs) {
            return lhs.top() > rhs.top();
        });
    };

    int curr = n;
    sort_ys();

    while (!ys.empty() && ys[0].top() >= curr) {
        for (auto it = begin(ys); it != end(ys);) {
            while (!it->empty() && it->top() > curr) it->pop();

            if (it->top() == curr) {
                it = ys.erase(it);
                --curr;
                break;
            } else {
                ++it;
            }
        }

        sort_ys();
    }

    return curr == 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
