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

    const ui_t power_of_two = ((8U * I) / n) > 31U ? 31U : ((8U * I) / n);
    const ui_t target_size = 1U << power_of_two;

    if (counts_by_intensity.size() <= target_size) {
        cout << "0\n";
    } else {
        auto l = counts_by_intensity.cbegin();
        auto r = l;
        ui_t sliding_total_count = l->second;

        for (ui_t i = 2; i <= target_size; ++i) {
            r = next(r);
            sliding_total_count += r->second;
        }

        auto ans = sliding_total_count;

        do {
            sliding_total_count -= l->second;
            ++l;

            ++r;
            sliding_total_count += r->second;

            ans = max(ans, sliding_total_count);
        } while (r != prev(counts_by_intensity.cend()));

        cout << n - ans << '\n';
    }
}
