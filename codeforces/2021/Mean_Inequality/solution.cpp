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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi solution(vi xs) {
    deque<int> ys(cbegin(xs), cend(xs));

    vi ans;

    while (!ys.empty()) {
        const auto a = ys.front();
        ys.pop_front();

        const auto b = ys.back();
        ys.pop_back();

        ans.push_back(b);
        ans.push_back(a);
    }

    // for (int i = 0; i < sz(xs) - 1; i += 2) {
    //     assert(i + 1 < sz(xs));
    //     swap(ans[i], ans[i + 1]);
    // }

    // for (int i = 1; i < sz(xs) - 1; ++i) {
    //     assert(2 * ans[i] != ans[i - 1] + ans[i + 1]);
    // }

    // if (sz(xs) > 2) {
    //     assert(2 * ans[0] != ans[1] + ans.back());
    // }


    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vi xs(n * 2, 0);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));
        cout << solution(move(xs)) << '\n';
    }

    return 0;
}
