#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(3 * n);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    deque<int> q(xbegin(xs), xend(xs));
    long long ans{};

    while (!q.empty()) {
        q.pop_back();
        ans += q.back();
        q.pop_back();

        q.pop_front();
    }

    cout << ans << '\n';
    return 0;
}
