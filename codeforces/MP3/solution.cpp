#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

int main() {
    ui_t n;
    ui_t I;
    cin >> n >> I;

    unordered_map<ui_t, ui_t> original_counts_by_intensity;
    map<ui_t, ui_t> counts_by_intensity;

    for (ui_t i = 0; i != n; ++i) {
        ui_t a;
        cin >> a;

        ++original_counts_by_intensity[a];
        ++counts_by_intensity[a];
    }

    ui_t ans{0};
    const ui_t power_of_two = ((8 * I) / n) > 31 ? 31 : ((8 * I) / n);
    const ui_t target_size = 1U << power_of_two;

    while (counts_by_intensity.size() > target_size) {
        const auto lo = counts_by_intensity.cbegin()->first;
        const auto hi = counts_by_intensity.crbegin()->first;

        if (counts_by_intensity[lo] < counts_by_intensity[hi]) {
            counts_by_intensity.erase(counts_by_intensity.cbegin());
            ans += original_counts_by_intensity[lo];
        } else {
            counts_by_intensity.erase(prev(counts_by_intensity.cend()));
            ans += original_counts_by_intensity[hi];
        }
    }

    cout << ans << '\n';
}
