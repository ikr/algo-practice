#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

bool straight(const int n, const int a, const int b) {
    assert(a <= b);
    return b - a <= a + n - b;
}

int lowest_upshift_index(const int n, const vector<int> &xs, const int i) {
    assert(i >= 0);
    const int w = xs.size();
    assert(i < w);

    if (i == 0 || !straight(n, xs[i - 1], xs[i])) return -1;
    if (straight(n, xs[0], xs[i])) return 0;

    int lo = 0;
    int hi = i - 1;

    while (hi - lo != 1) {
        const int mid = lo + (hi - lo) / 2;
        if (straight(n, xs[mid], xs[i])) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    return hi;
}

int highest_downshift_index(const int n, const vector<int> &xs, const int i) {
    assert(i >= 0);
    const int w = xs.size();
    assert(i < w);

    if (i == w - 1 || !straight(n, xs[i], xs[i + 1])) return -1;
    if (straight(n, xs[i], xs[w - 1])) return w - 1;

    int lo = i + 1;
    int hi = w - 1;

    while (hi - lo != 1) {
        const int mid = lo + (hi - lo) / 2;
        if (straight(n, xs[i], xs[mid])) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo;
}

ll solve(const int n, const vector<int> &xs) {
    const int w = xs.size();

    cout << "\nxs: " << xs << '\n';
    for (int i = 0; i < w; ++i) {
        cout << i << ':' << lowest_upshift_index(n, xs, i) << ' ';
    }
    cout << '\n';
    for (int i = 0; i < w; ++i) {
        cout << i << ':' << highest_downshift_index(n, xs, i) << ' ';
    }
    cout << '\n';

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int w, n;
        cin >> w >> n;
        vector<int> xs(w, 0);
        for (auto &x : xs) {
            cin >> x;
            --x;
        }
        sort(begin(xs), end(xs));

        cout << "Case #" << i << ": " << solve(n, xs) << '\n';
    }

    return 0;
}
