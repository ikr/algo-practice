#include <bits/stdc++.h>
using namespace std;

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

vi to_pref_suff_form(const string &xs, const char x, vi rle) {
    const bool is_first = (xs[0] == x);
    const bool is_last = (xs.back() == x);

    if (!is_first) rle.insert(cbegin(rle), 0);
    if (!is_last) rle.push_back(0);

    sort(next(begin(rle)), prev(end(rle)), greater<int>{});
    return rle;
}

int max_monochrome_pants(const string &xs, const char x, const vi &rle,
                         const int k) {
    if (rle.empty()) return -1;

    const bool is_first = (xs[0] == x);
    const bool is_last = (xs.back() == x);
    if (is_first && is_last && sz(rle) == 1) return rle[0];
    if (k == 0) return -1;

    const auto psf = to_pref_suff_form(xs, x, rle);

    if (k == 1) {
        return is_first && is_last ? (psf[0] + psf.back())
                                   : max(psf[0], psf.back());
    }

    if (sz(psf) <= 2) return accumulate(cbegin(psf), cend(psf), 0);

    const auto inner_sz = sz(psf) - 2;

    return psf[0] + psf.back() +
           accumulate(next(cbegin(psf)),
                      next(cbegin(psf), min(1 + inner_sz, k)), 0);
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

int oracle(const string &s, const int k) {
    const int n = sz(s);

    {
        int ok = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] != s[0]) {
                ok = 0;
            }
        }
        if (ok) {
            return n;
        }
    }
    if (k == 0) {
        return -1;
    }
    vector<vector<int>> a(26);
    int cnt = 1;
    for (int i = 1; i <= n; ++i) {
        if (i == n || s[i] != s[i - 1]) {
            a[s[i - 1] - 'A'].push_back(cnt);
            cnt = 1;
        } else {
            cnt += 1;
        }
    }
    int ans = 0;
    if (k > 1) {
        for (int i = 0; i < 26; ++i) {
            vector<int> b = a[i];
            sort(b.begin(), b.end(), greater<int>());
            int tmp = 0;
            for (int j = 0; j < b.size() && j < k - 1; ++j) {
                tmp += b[j];
            }
            ans = max(ans, tmp);
        }
    }
    {
        vector<int> b = a[s[0] - 'A'];
        int tmp = b[0];
        b.erase(b.begin());
        sort(b.begin(), b.end(), greater<int>());
        for (int j = 0; j < b.size() && j < k - 1; ++j) {
            tmp += b[j];
        }
        ans = max(ans, tmp);
    }
    {
        vector<int> b = a[s.back() - 'A'];
        int tmp = b.back();
        b.pop_back();
        sort(b.begin(), b.end(), greater<int>());
        for (int j = 0; j < b.size() && j < k - 1; ++j) {
            tmp += b[j];
        }
        ans = max(ans, tmp);
    }
    if (s[0] == s.back()) {
        vector<int> b = a[s.back() - 'A'];
        int tmp = b[0] + b.back();
        b.erase(b.begin());
        b.pop_back();
        sort(b.begin(), b.end(), greater<int>());
        for (int j = 0; j < b.size() && j < k - 1; ++j) {
            tmp += b[j];
        }
        ans = max(ans, tmp);
    }
    return ans;
}

template <typename T> struct RndInt final {
    RndInt(const T lo, const T hi) : m_gen{random_device{}()}, m_dist{lo, hi} {}
    T next() { return m_dist(m_gen); }

  private:
    mt19937 m_gen;
    uniform_int_distribution<T> m_dist;
};

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

    RndInt az(0, AZ - 1);
    RndInt nn(99999, 100000);

    for (t = 0; t < 1; ++t) {
        const int n = nn.next();

        string xs(n, ' ');
        for (int i = 0; i < n; ++i) {
            xs[i] = chof(inof('A') + az.next());
        }

        for (int k = 0; k <= n; ++k) {
            const auto own = max_monochrome_pants(xs, k);
            const auto orc = oracle(xs, k);

            if (own != orc) {
                cerr << "\n\nFound! " << xs << " " << own << "/" << orc << endl;
                return 0;
            }

            if (k % 1000 == 0) {
                cerr << k << ' ';
            }
        }
    }

    return 0;
}
