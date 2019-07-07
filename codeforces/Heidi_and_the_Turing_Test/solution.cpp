#include <bits/stdc++.h>

using namespace std;

using XY = pair<int, int>;

optional<int> square_size(const XY p1, const XY p2, const XY p3, const XY p4) {
    vector<XY> ps{p1, p2, p3, p4};

    sort(ps.begin(), ps.end(),
         [](const auto a, const auto b) { return a.first < b.first; });

    const auto width = ps[3].first - ps[0].first;

    sort(ps.begin(), ps.end(),
         [](const auto a, const auto b) { return a.second < b.second; });

    const auto height = ps[3].second - ps[0].second;

    return (width == height) ? make_optional(width) : nullopt;
}

int main() {
    int min_count_per_side;
    cin >> min_count_per_side;

    const auto sz = 4 * min_count_per_side + 1;

    vector<XY> ps(sz);
    for (auto &p : ps) cin >> p.first >> p.second;

    map<int, int> points_count_by_square_size;
    multimap<XY, int> square_size_by_point;

    for (auto i = 0; i != sz - 3; ++i) {
        for (auto j = 1; j != sz - 2; ++j) {
            for (auto k = 2; k != sz - 1; ++k) {
                for (auto l = 3; l != sz; ++l) {
                    const auto ssz = square_size(ps[i], ps[j], ps[k], ps[l]);

                    if (ssz) {
                        points_count_by_square_size[*ssz] += 4;

                        for (const auto p : {ps[i], ps[j], ps[k], ps[l]}) {
                            square_size_by_point.insert({p, *ssz});
                        }
                    }
                }
            }
        }
    }

    const auto actual_square_size = points_count_by_square_size.rbegin()->first;

    for (const auto p : ps) {
        map<int, int> own_count_by_square_size;

        const auto [first, last] = square_size_by_point.equal_range(p);

        for_each(first, last,
                 [&own_count_by_square_size](const auto &the_pair) {
                     const auto sz = the_pair.second;
                     ++own_count_by_square_size[sz];
                 });

        if (own_count_by_square_size.empty() ||
            own_count_by_square_size.rbegin()->first != actual_square_size) {
            cout << p.first << ' ' << p.second << '\n';
            break;
        }
    }
}
