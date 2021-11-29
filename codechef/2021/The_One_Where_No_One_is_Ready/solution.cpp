#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = inof('Z') - inof('A') + 1;

vvi runlength_encode(const string &xs) {
    char pants = xs[0];
    char length = 1;
    vvi ans(AZ);

    for (int i = 1; i < sz(xs); ++i) {
        const auto x = xs[i];

        if (x == pants) {
            ++length;
            continue;
        }

        ans[inof(pants) - inof('A')].push_back(length);
        pants = x;
        length = 1;
    }

    ans[inof(pants) - inof('A')].push_back(length);
    return ans;
}

int max_monochrome_pants(const string &xs, const char x, const vi &rle,
                         const int k) {
    if (rle.empty()) return -1;

    const bool is_first = (xs[0] == x);
    const bool is_last = (xs.back() == x);

    if (k == 0) {
        return (is_first && is_last && sz(rle) == 1) ? rle[0] : -1;
    }

    vi ss(sz(rle), 0);
    partial_sum(cbegin(rle), cend(rle), begin(ss));

    const auto sum_for = [&ss](const int l, const int r) -> int {
        return ss[r - 1] - (l ? ss[l - 1] : 0);
    };

    int ans = -1;

    for (int i = 0; i + k < sz(rle); ++i) {
        const auto r = [&]() -> int {
            int rr = i + k + 1;
            if (i == 0 && !is_first) --rr;
            if (rr == sz(rle) && !is_last) --rr;
            return rr;
        }();

        ans = max(ans, sum_for(i, r));
    }

    return ans;
}

int max_monochrome_pants(const string &xs, const int k) {
    const auto rles = runlength_encode(xs);

    int ans = -1;

    for (int i = 0; i < AZ; ++i) {
        ans =
            max(ans, max_monochrome_pants(xs, chof(inof('A') + i), rles[i], k));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs(n, ' ');
        cin >> xs;

        cout << max_monochrome_pants(xs, k) << '\n';
    }

    return 0;
}
