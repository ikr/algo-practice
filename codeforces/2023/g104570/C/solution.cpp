#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> run_length_encode(const string &xs) {
    vector<pair<char, int>> ans{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i] == ans.back().first) {
            ++(ans.back().second);
        } else {
            ans.emplace_back(xs[i], 1);
        }
    }
    return ans;
}

vector<int> tri_series_lengths(const string &xs, const string &tri) {
    assert(sz(tri) == 3);
    vector<int> ans;

    for (string::size_type i = 0;;) {
        if (i >= xs.size()) break;
        i = xs.find(tri, i);
        if (i == xs.npos) break;

        i += 3;

        int len = 3;
        for (string::size_type j = i + 1; j < xs.size(); j += 2) {
            if (xs[j - 1] == tri[1] && xs[j] == tri[2]) {
                len += 2;
                i += 2;
            } else {
                break;
            }
        }
        ans.push_back(len);
    }

    return ans;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

ll super_palindrome_substrings_num(const string &xs) {
    ll ans{};

    for (const auto &tri : vector<string>{"101", "010"}) {
        const auto ls = tri_series_lengths(xs, tri);
        // cerr << "ls:" << ls << endl;
        for (const auto l : ls) {
            assert(l >= 3);
            const auto d = (l - 3) / 2;
            ++ans;
            ans += 2 * d;

            const auto h = max(0, l - 5) / 2;
            ans += h;
        }
    }

    const auto rle = run_length_encode(xs);
    for (const auto &[_, len] : rle) {
        if (len < 3) continue;
        if (len == 3) {
            ++ans;
            continue;
        }

        ll d = len;
        d = d * (d + 1LL) / 2LL;
        d -= len;
        d -= len - 1;

        ans += d;
    }
    return ans;
}

bool is_pali(const string &xs) {
    for (int i = 0; i < sz(xs) / 2; ++i) {
        if (xs[i] != xs[sz(xs) - 1 - i]) return false;
    }
    return true;
}

bool is_super_pali(const string &s) {
    if (sz(s) < 3) return false;
    return is_pali(s) && is_pali(s.substr(0, sz(s) - 2));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << super_palindrome_substrings_num(xs) << '\n';

        // cerr << "pali:\n";
        // for (int i = 0; i < n; ++i) {
        //     for (int j = i; j < n; ++j) {
        //         if (is_super_pali(xs.substr(i, j - i + 1))) {
        //             cerr << xs.substr(i, j - i + 1) << endl;
        //         }
        //     }
        // }
        // cerr << endl;
    }

    return 0;
}
