#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

constexpr bool intersect(const pi ab, const pi cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    return !(b < c || d < a);
}

constexpr pi span(const pi ab, const pi cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    return {min({a, b, c, d}), max({a, b, c, d})};
}

vector<pi> unite_intersecting(vector<pi> xs) {
    sort(begin(xs), end(xs));
    vector<pi> ans;
    ans.reserve(xs.size() / 16);

    for (const auto cd : xs) {
        if (ans.empty()) {
            ans.push_back(cd);
        } else {
            const auto ab = ans.back();
            if (intersect(ab, cd)) {
                ans.back() = span(ab, cd);
            }
        }
    }

    return ans;
}

int total_overlap(vector<pi> xs, vector<pi> ys) {
    ys = unite_intersecting(ys);
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pi> xs(n);
        for (auto &[a, b] : xs) cin >> a >> b;

        vector<pi> ys(m);
        for (auto &[a, b] : ys) cin >> a >> b;

        cout << total_overlap(move(xs), move(ys)) << '\n';
    }

    return 0;
}
