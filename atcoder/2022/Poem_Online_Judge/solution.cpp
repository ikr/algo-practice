#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int best_original_submission_index(const vector<pair<string, int>> &sts) {
    auto [_, best_t] = sts[0];
    int best_i = 0;
    set<string> seen{sts[0].first};

    for (int i = 1; i < sz(sts); ++i) {
        const auto &[s, t] = sts[i];
        if (seen.count(s)) continue;

        if (t > best_t) {
            best_t = t;
            best_i = i;
        }

        seen.insert(s);
    }

    return best_i;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pair<string, int>> sts(N);
    for (auto &[s, t] : sts) cin >> s >> t;

    cout << (best_original_submission_index(sts) + 1) << '\n';
    return 0;
}
