#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

int main() {
    ui_t n;
    ui_t I;
    cin >> n >> I;

    map<ui_t, ui_t> counts_by_intensity;

    for (ui_t i = 0U; i != n; ++i) {
        ui_t a;
        cin >> a;
        ++counts_by_intensity[a];
    }

    ui_t ans{0U};
    const ui_t power_of_two = ((8U * I) / n) > 31U ? 31U : ((8U * I) / n);
    const ui_t target_size = 1U << power_of_two;

    while (counts_by_intensity.size() > target_size) {
        auto lo_it = counts_by_intensity.begin();
        auto hi_it = counts_by_intensity.rbegin();

        if (lo_it->second <= hi_it->second) {
            if (lo_it->second == 1)
                counts_by_intensity.erase(counts_by_intensity.cbegin());
            else
                --lo_it->second;
        } else {
            if (hi_it->second == 1)
                counts_by_intensity.erase(prev(counts_by_intensity.cend()));
            else
                --hi_it->second;
        }

        ++ans;
    }

    cout << ans << '\n';
}
