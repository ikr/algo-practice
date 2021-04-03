#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<bool> present_chars(const string &xs) {
    vector<bool> ans(26, false);
    for (const char x : xs) ans[x - 'a'] = true;
    return ans;
}

vector<set<int>> letter_indices(const string &xs) {
    vector<set<int>> ans(26);
    for (int i = 0; i < sz(xs); ++i) ans[xs[i] - 'a'].insert(i);
    return ans;
}

vector<pii> gather_ranges(const vector<set<int>> &idx) {
    vector<pii> ans(sz(idx));

    transform(cbegin(idx), cend(idx), begin(ans), [](const auto &xss) {
        return xss.empty() ? pii{INT_MAX, -1}
                           : pii{*cbegin(xss), *crbegin(xss)};
    });

    return ans;
}

string max_str(const string &xs) {
    const auto idx = letter_indices(xs);
    auto present = present_chars(xs);
    auto ranges = gather_ranges(idx);

    const auto count_present = [&]() -> int {
        return inof(count(cbegin(present), cend(present), true));
    };

    const auto next_index = [&](const char x, const int i) -> int {
        const auto it = idx[x - 'a'].upper_bound(i);
        return it == cend(idx[x - 'a']) ? -1 : *it;
    };

    const auto can_be_first = [&](const char x) -> bool {
        if (!present[x - 'a']) return false;
        if (count_present() == 1) return true;

        const auto [my_lo, my_hi] = ranges[x - 'a'];
        for (int i = 0; i < sz(present); ++i) {
            if ('a' + i == x || !present[i]) continue;

            const auto [_, their_hi] = ranges[i];
            if (my_lo > their_hi) return false;
        }

        return true;
    };

    const auto best_first = [&]() -> char {
        for (char x = 'z'; x >= 'a'; --x) {
            if (can_be_first(x)) return x;
        }

        assert(false && "/o\\");
        return ' ';
    };

    string ans;

    while (count_present() > 0) {
        const char x = best_first();
        const int cut = ranges[x - 'a'].first;
        ans += x;
        present[x - 'a'] = false;

        for (char y = 'a'; y <= 'z'; ++y) {
            if (!present[y - 'a']) continue;
            ranges[y - 'a'].first = next_index(y, cut);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;
        cout << max_str(xs) << '\n';
    }

    return 0;
}
