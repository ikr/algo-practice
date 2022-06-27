#include <iostream>
#include <set>
#include <vector>
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

vector<int> solve(const vector<int> &xs) {
    multiset<int> cit_pq;
    vector<int> result;
    result.reserve(sz(xs));
    int curr = 0;

    for (const auto x : xs) {
        cit_pq.insert(x);
        while (!cit_pq.empty() && *cbegin(cit_pq) <= curr) {
            cit_pq.erase(cbegin(cit_pq));
        }

        if (sz(cit_pq) >= curr + 1) ++curr;
        result.push_back(curr);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
