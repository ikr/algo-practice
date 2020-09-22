#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> interleave(const vector<int> &xs, const int cheaps) {
    const int n = xs.size();
    vector<int> ans(n, 0);
    ans[0] = xs.back();
    int k = 1;

    for (int i = cheaps - 1, j = n - 2; i >= 0; --i, --j) {
        ans[k++] = xs[i];
        ans[k++] = xs[j];
    }

    for (int i = cheaps; k < n && i < n - 1 - cheaps; ++i) {
        ans[k++] = xs[i];
    }

    return ans;
}

bool is_possible(const vector<int> &xs, const int cheaps) {
    const int n = xs.size();
    if (xs.back() <= xs[cheaps - 1]) return false;

    for (int i = cheaps - 1, j = n - 2; i >= 0; --i, --j) {
        if (i >= j || xs[i] >= xs[j]) return false;
    }

    return true;
}

pair<int, vector<int>> solve(vector<int> &xs) {
    const int n = xs.size();
    if (n <= 2) return {0, xs};

    sort(begin(xs), end(xs));

    int lo = 1;
    if (!is_possible(xs, lo)) return {0, xs};
    int hi = n % 2 == 0 ? (n / 2 - 1) : n / 2;
    if (is_possible(xs, hi)) return {hi, interleave(xs, hi)};

    while (lo < hi) {
        if (lo + 1 == hi) {
            return is_possible(xs, hi) ? pair{hi, interleave(xs, hi)}
                                       : pair{lo, interleave(xs, lo)};
        }

        const int mid = lo + (hi - lo) / 2;
        if (is_possible(xs, mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    return {lo, interleave(xs, lo)};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;
    const auto [cnt, ys] = solve(xs);

    cout << cnt << '\n';
    cout << ys << '\n';

    return 0;
}
