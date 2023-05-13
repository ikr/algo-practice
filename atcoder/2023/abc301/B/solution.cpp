#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> fill_gaps(const vector<int> &xs) {
    vector<int> ans{xs[0]};

    for (int i = 1; i < sz(xs); ++i) {
        int a = xs[i - 1];
        int b = xs[i];
        if (abs(a - b) == 1) {
            ans.push_back(b);
            continue;
        }

        if (a < b) {
            while (ans.back() + 1 != b) {
                ans.push_back(ans.back() + 1);
            }
        } else {
            assert(a > b);
            while (ans.back() - 1 != b) {
                ans.push_back(ans.back() - 1);
            }
        }
        ans.push_back(b);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << fill_gaps(xs) << '\n';
    return 0;
}
