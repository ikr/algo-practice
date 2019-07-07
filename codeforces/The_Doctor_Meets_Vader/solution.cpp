#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

struct Base {
    ui_t d_pwr;
    ui_t gold;
};

int main() {
    ui_t s;
    ui_t b;
    cin >> s >> b;

    vector<ui_t> a_pwr(s, 0);
    for (auto &a : a_pwr) {
        cin >> a;
    }

    vector<Base> bases(b);
    for (auto &base : bases) {
        ui_t d;
        ui_t g;
        cin >> d >> g;

        base = {d, g};
    }

    sort(bases.begin(), bases.end(),
         [](const auto b1, const auto b2) { return b1.d_pwr > b2.d_pwr; });

    ui_t ship_index = 0;
    for (const auto a : a_pwr) {
        if (ship_index) {
            cout << ' ';
        }

        ui_t ans = 0;

        for (auto it = lower_bound(
                 bases.cbegin(), bases.cend(), a,
                 [](const Base &base, const ui_t a) { return base.d_pwr > a; });
             it != bases.cend(); ++it) {
            ans += it->gold;
        }

        cout << ans;

        ++ship_index;
    }

    cout << '\n';

    return 0;
}
