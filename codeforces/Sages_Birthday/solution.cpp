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
    vector<int> ans{xs[0]};
    ans.reserve(cheaps * 2 + 1);

    int lo = 1;
    int hi = n - 1;

    for (int l = 1, r = n - 1; l <= cheaps; ++l, --r) {
        ans.push_back(xs[r]);
        hi = r - 1;
        ans.push_back(xs[l]);
        lo = l + 1;

        if (l == cheaps && n % 2 == 0) {
            ans.push_back(xs[r - 1]);
            hi = r - 2;
        }
    }

    for (int i = lo; i <= hi; ++i) ans.push_back(xs[i]);

    return ans;
}

bool is_possible(const vector<int> &xs, const int cheaps) {
    const int n = xs.size();
    const int i = cheaps;
    const int j = n - 1 - cheaps + 1;
    return i < j && xs[i] > xs[j];
}

pair<int, vector<int>> solve(vector<int> &xs) {
    const int n = xs.size();
    if (n <= 2) return {0, xs};

    sort(rbegin(xs), rend(xs));

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
