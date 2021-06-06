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

using iter = deque<int>::const_iterator;

static constexpr int INF = 1e9;

iter closest(const iter first, const iter last, const int x) {
    iter ans = last;
    int best = INF;

    for (iter it = first; it != last; ++it) {
        if (abs(x - *it) < best) {
            best = abs(x - *it);
            ans = it;
        }
    }

    assert(ans != last);
    return ans;
}

int min_cooking_time(deque<int> xs) {
    int ans = 0;
    int b = 0;

    while (!xs.empty()) {
        if (b == 0) {
            b = *crbegin(xs);
            xs.erase(prev(cend(xs)));
        }

        int a = 0;
        if (!xs.empty()) {
            if (b > *cbegin(xs)) {
                a += *cbegin(xs);
                xs.erase(cbegin(xs));
            } else {
                a += *crbegin(xs);
                xs.erase(prev(cend(xs)));
            }
        }

        if (a <= b) {
            b -= a;
            ans += a;
        } else {
            a -= b;
            ans += b;
            b = a;
        }
    }

    ans += b;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    deque<int> xs;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        xs.push_back(x);
    }
    sort(begin(xs), end(xs));

    cout << min_cooking_time(move(xs)) << '\n';
    return 0;
}
