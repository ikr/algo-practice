#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string join(const string &glue, const vector<string> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += t;
    }

    return ans;
}

template <typename T>
vector<vector<T>> cartesian_product(const vector<vector<T>> &src) {
    vector<vector<T>> result;
    if (src.empty() || any_of(cbegin(src), cend(src),
                              [](const auto &xs) { return xs.empty(); })) {
        return result;
    }

    result.push_back(vector<T>{});
    for (const auto &xs : src) {
        vector<vector<T>> next_gen;

        for (const auto x : xs) {
            for (auto curr : result) {
                curr.push_back(x);
                next_gen.push_back(curr);
            }
        }

        result = next_gen;
    }

    return result;
}

string suggest_username(vector<string> xs, const vector<string> &zs) {
    const set<string> forbidden(cbegin(zs), cend(zs));

    if (sz(xs) == 1) {
        if (sz(xs[0]) < 3) return "-1";
        return forbidden.count(xs[0]) ? string{"-1"} : xs[0];
    }

    const auto min_length = sz(join("_", xs));
    if (min_length > 16) return "-1";

    const auto max_insertions = 16 - min_length;
    const auto insertion_places = sz(xs) - 1;

    do {
        {
            const auto u0 = join("_", xs);
            if (!forbidden.count(u0)) return u0;
        }

        auto parts0 = xs;
        for (int i = 0; i < sz(parts0) - 1; ++i) {
            parts0[i] += '_';
        }

        for (int insertions = 1; insertions <= max_insertions; ++insertions) {
            vector<int> cyl(insertion_places, 0);
            iota(begin(cyl), end(cyl), 0);
            vector<vector<int>> spacer_placements(insertions, cyl);

            for (const auto &cs : cartesian_product(spacer_placements)) {
                auto parts = parts0;

                for (const auto i : cs) {
                    parts[i] += '_';
                }

                const auto u = join("", parts);
                if (!forbidden.count(u)) return u;
            }
        }

    } while (next_permutation(begin(xs), end(xs)));

    return "-1";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<string> xs(N);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    vector<string> zs(M);
    for (auto &z : zs) cin >> z;

    cout << suggest_username(move(xs), zs) << '\n';
    return 0;
}
