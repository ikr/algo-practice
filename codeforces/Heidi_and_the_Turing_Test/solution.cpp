#include <bits/stdc++.h>

using namespace std;

using XY = pair<int, int>;

bool are_on_square_in_order(const XY p1, const XY p2, const XY p3,
                            const XY p4) {
    return abs(p1.first - p3.first) == abs(p2.second - p4.second);
}

bool are_on_square(const XY p1, const XY p2, const XY p3, const XY p4) {
    vector<XY> ps{p1, p2, p3, p4};
    sort(ps.begin(), ps.end());

    do {
        if (are_on_square_in_order(ps[0], ps[1], ps[2], ps[3])) return true;
    } while (next_permutation(ps.begin(), ps.end()));

    return false;
}

int main() {
    int min_count_per_side;
    cin >> min_count_per_side;

    const auto sz = 4 * min_count_per_side + 1;

    vector<XY> ps(sz);
    for (auto &p : ps) cin >> p.first >> p.second;

    set<XY> squared;

    for (auto i = 0; i != sz - 3; ++i) {
        for (auto j = 1; j != sz - 2; ++j) {
            for (auto k = 2; k != sz - 1; ++k) {
                for (auto l = 3; l != sz; ++l) {
                    if (are_on_square(ps[i], ps[j], ps[k], ps[l])) {
                        squared.insert({ps[i], ps[j], ps[k], ps[l]});
                    }
                }
            }
        }
    }

    for (const auto p : ps) {
        if (!squared.count(p)) {
            cout << p.first << ' ' << p.second << '\n';
            break;
        }
    }
}
