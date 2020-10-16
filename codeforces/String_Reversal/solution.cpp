#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr int SZ = 'z' - 'a' + 1;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

string reversed(string s) {
    reverse(begin(s), end(s));
    return s;
}

vector<int> permutation_of_reversed(const string &s) {
    const auto rs = reversed(s);
    const int n = s.size();
    vector<int> ans(n, -1);
    vector<deque<int>> idx(SZ);

    for (int i = 0, j = 0; i < n;) {
        const char x = s[i];
        const char y = rs[j];

        idx[y - 'a'].push_back(j);

        if (!idx[x - 'a'].empty()) {
            ans[i] = idx[x - 'a'].front();
            idx[x - 'a'].pop_front();
            ++i;
        }

        if (j < n - 1) ++j;
    }

    return ans;
}

ll count_inversions(const vector<int> &xs) {
    const int n = xs.size();
    ll ans = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (xs[i] > xs[j]) ++ans;
        }
    }

    return ans;
}

ll min_swaps(const string &s) {
    return count_inversions(permutation_of_reversed(s));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string s(n, ' ');
    cin >> s;

    cout << min_swaps(s) << '\n';
    return 0;
}
