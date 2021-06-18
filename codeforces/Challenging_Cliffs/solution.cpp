#include <bits/stdc++.h>
#include <functional>
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

int score(const vi &xs) {
    vi ds(sz(xs));
    adjacent_difference(cbegin(xs), cend(xs), begin(ds));

    return count_if(next(cbegin(ds)), cend(ds),
                    [](const int x) { return x >= 0; });
}

vi optimal_course(vi xs) {
    sort(begin(xs), end(xs));

    vi ds(sz(xs));
    adjacent_difference(cbegin(xs), cend(xs), begin(ds));
    const int lo = *min_element(next(cbegin(ds)), cend(ds));

    int best_i = -1;
    int best_score = 0;

    for (int i = 0; i < sz(xs) - 1; ++i) {
        if (xs[i + 1] - xs[i] > lo) continue;

        int score = sz(xs) - 1;
        if (xs[i] > xs[0]) --score;
        if (xs[i + 1] < xs.back()) --score;

        if (score > best_score) {
            best_i = i;
            best_score = score;
        }
    }

    assert(best_i >= 0);
    swap(xs[0], xs[best_i]);
    swap(xs[best_i + 1], xs.back());

    vi ys = xs;
    sort(next(begin(ys)), prev(end(ys)), greater<int>{});

    return score(xs) > score(ys) ? xs : ys;
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
        cout << optimal_course(xs) << '\n';
    }

    return 0;
}
