#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e10;
using tri = tuple<char, char, char>;

bool confirm_pattern(const string &t, const tri p) {
    const auto [a, b, c] = p;
    const int n = t.size();

    for (int i = 0; i < n; i += 3) {
        if (t[i] != a) return false;
        if (i + 1 < n && t[i + 1] != b) return false;
        if (i + 2 < n && t[i + 2] != c) return false;
    }

    return true;
}

ll max_shift(const int first, const int n) {
    const ll dividend = M * 3LL - first - n;
    return dividend / 3LL;
}

ll count_entries(const string &t) {
    const int n = t.size();

    if (n == 1) {
        return t[0] == '0' ? M : 2LL * M;
    }

    if (n == 2) {
        if (t == "00") return 0;
        if (t == "01") return M - 1LL;
        return M;
    }

    const auto pre = t.substr(0, 3);

    if (pre == "011") {
        if (!confirm_pattern(t, {'0', '1', '1'})) return 0;
        return max_shift(2, n) + 1LL;
    }

    if (pre == "101") {
        if (!confirm_pattern(t, {'1', '0', '1'})) return 0;
        return max_shift(1, n) + 1LL;
    }

    if (pre == "110") {
        if (!confirm_pattern(t, {'1', '1', '0'})) return 0;
        return max_shift(0, n) + 1LL;
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string t(n, ' ');
    cin >> t;

    cout << count_entries(t) << '\n';
    return 0;
}
