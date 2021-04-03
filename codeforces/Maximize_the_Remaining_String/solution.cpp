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

vector<pii> letter_index_ranges(const string &xs) {
    vector<pii> ans(26, {INT_MAX, -1});

    for (int i = 0; i < sz(xs); ++i) {
        auto &[lo, hi] = ans[xs[i] - 'a'];
        lo = min(lo, i);
        hi = max(hi, i);
    }

    return ans;
}

string max_str(const string &xs) {
    auto present = present_chars(xs);
    auto ranges = letter_index_ranges(xs);

    const auto count_present = [&]() -> int {
        return inof(count(cbegin(present), cend(present), true));
    };

    const auto can_be_first = [&](const char x) -> bool {
        if (!present[x - 'a']) return false;
        if (count_present() == 1) return true;

        const auto [my_lo, my_hi] = ranges[x];
        for (int i = 0; i < sz(present); ++i) {
            if (i == x) continue;

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
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    assert(max_str("codeforces") == "odfrces");
    assert(max_str("aezakmi") == "ezakmi");
    assert(max_str("abacaba") == "cba");
    assert(max_str("convexhull") == "convexhul");
    assert(max_str("swflldjgpaxs") == "wfldjgpaxs");
    assert(max_str("myneeocktxpqjpz") == "myneocktxqjpz");
    assert(max_str("jpimokmwii") == "jpokmwi");
    assert(max_str("gqeojmgfpguxiu") == "qeojmgfpxiu");

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;
        cout << max_str(xs) << '\n';
    }

    return 0;
}
