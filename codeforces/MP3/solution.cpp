#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

int main() {
    ui_t n;
    ui_t I;
    cin >> n >> I;

    map<ui_t, ui_t> counts_by_intensity;

    for (ui_t i = 0; i != n; ++i) {
        ui_t a;
        cin >> a;
        ++counts_by_intensity[a];
    }

    ui_t ans{0};
    const ui_t power_of_two = ((8 * I) / n) > 31 ? 31 : ((8 * I) / n);
    const ui_t target_size = 1U << power_of_two;

    while (counts_by_intensity.size() > target_size) {
        const auto lo_it = counts_by_intensity.cbegin();
        const auto hi_it = counts_by_intensity.crbegin();

        if (lo_it->second <= hi_it->second) {
            ans += lo_it->second;
            counts_by_intensity.erase(counts_by_intensity.cbegin());
        } else {
            ans += hi_it->second;
            counts_by_intensity.erase(prev(counts_by_intensity.cend()));
        }
    }

    cout << ans << '\n';
}
