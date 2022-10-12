#include <bits/stdc++.h>
using namespace std;

using tri = tuple<int, int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<tri> find_program(multiset<int> xs) {
    vector<tri> result;

    while (!xs.empty()) {
        const auto [ti, tj, tk] = [&]() -> tri {
            for (auto i = cbegin(xs); i != cend(xs); ++i) {
                for (auto j = cbegin(xs); j != prev(cend(xs)); ++j) {
                    if (j == i) continue;

                    for (auto k = next(j); k != cend(xs); ++k) {
                        if (k == i) continue;
                        if (((*j) ^ (*k)) == *i) return {*i, *j, *k};
                    }
                }
            }

            assert(false && "/o\\");
            return {-1, -1, -1};
        }();

        cerr << "found " << ti << ' ' << tj << ' ' << tk << endl;

        if (ti == tj && tj == tk) {
            result.emplace_back(ti, tj, tk);
        } else {
            result.emplace_back(ti, tj, tk);
            result.emplace_back(ti, ti, ti);
        }

        xs.erase(xs.find(ti));
        xs.erase(xs.find(tj));
        xs.erase(xs.find(tk));
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        sort(rbegin(xs), rend(xs));
        while (!xs.empty() && xs.back() == 0) xs.pop_back();

        const auto ops = find_program(multiset<int>(crbegin(xs), crend(xs)));
        cout << sz(ops) << '\n';
        for (const auto &[a, b, c] : ops) {
            cout << a << ' ' << b << ' ' << c << '\n';
        }
    }

    return 0;
}
