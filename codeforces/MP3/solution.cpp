#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned long long;

int main() {
    ui_t n;
    ui_t I;
    cin >> n >> I;

    unordered_map<ui_t, ui_t> original_counts_by_intensity;
    map<ui_t, ui_t> counts_by_intensity;
    unordered_set<ui_t> intensities;

    for (ui_t i = 0; i != n; ++i) {
        ui_t a;
        cin >> a;

        ++original_counts_by_intensity[a];
        ++counts_by_intensity[a];
        intensities.insert(a);
    }

    ui_t ans{0};

    const ui_t target_size = 1 << ((8 * I) / n);
    while (intensities.size() > target_size) {
        const auto lo = counts_by_intensity.cbegin()->first;
        const auto hi = counts_by_intensity.crbegin()->first;

        if (counts_by_intensity[lo] < counts_by_intensity[hi]) {
            auto next_lo_it = counts_by_intensity.cbegin();
            ++next_lo_it;
            const auto next_lo = next_lo_it->first;

            counts_by_intensity.erase(lo);
            intensities.erase(lo);

            counts_by_intensity[next_lo] += original_counts_by_intensity[lo];
            ans += original_counts_by_intensity[lo];
        } else {
            auto next_hi_it = counts_by_intensity.crbegin();
            ++next_hi_it;
            const auto next_hi = next_hi_it->first;

            counts_by_intensity.erase(hi);
            intensities.erase(hi);

            counts_by_intensity[next_hi] += original_counts_by_intensity[hi];
            ans += original_counts_by_intensity[hi];
        }
    }

    cout << ans << '\n';
}
