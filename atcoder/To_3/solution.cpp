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

vector<int> digits_reversed(ll x) {
    vector<int> ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

pair<int, int> gather_mod12_counts(const vector<int> &xs) {
    int c1 = 0;
    int c2 = 0;

    for (const int x : xs) {
        const int r = x % 3;
        if (r == 1) {
            ++c1;
        } else if (r == 2) {
            ++c2;
        }
    }

    return {c1, c2};
}

int recur(const int c1, const int c2) {
    if ((c1 + 2 * c2) % 3 == 0) return 0;
}

int min_removals(const ll x) {
    const auto [c1, c2] = gather_mod12_counts(digits_reversed(x));
    return recur(c1, c2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll x;
    cin >> x;

    return 0;
}
