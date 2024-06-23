#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> remove_ones(const vector<int> &xs) {
    vector<int> result;
    for (const auto x : xs) {
        if (x != 1) result.push_back(x);
    }
    return result;
}

int min_value(const string &s) {
    if (sz(s) > 3 && count(cbegin(s), cend(s), '0')) return 0;

    int lo = stoi(s.substr(0, 2));
    int i0 = 0;

    for (int i = 0; i < sz(s) - 1; ++i) {
        const auto candidate = stoi(s.substr(i, 2));
        if (candidate < lo) {
            lo = candidate;
            i0 = i;
        }
    }

    vector<int> xs;
    for (int i = 0; i < sz(s);) {
        if (i == i0) {
            xs.push_back(stoi(s.substr(i, 2)));
            i += 2;
        } else {
            xs.push_back(stoi(s.substr(i, 1)));
            ++i;
        }
    }

    if (sz(xs) == 1) return xs[0];

    if (sz(xs) == 2) {
        return min(xs[0] + xs[1], xs[0] * xs[1]);
    }

    if (count(cbegin(xs), cend(xs), 0)) return 0;

    if (all_of(cbegin(xs), cend(xs), [](const int x) { return x == 1; })) {
        return 1;
    }

    xs = remove_ones(xs);
    return accumulate(cbegin(xs), cend(xs), 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;
        assert(sz(s) == n);

        cout << min_value(s) << '\n';
    }

    return 0;
}
