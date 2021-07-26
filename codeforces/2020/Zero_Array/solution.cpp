#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned long long;

bool can_split_in_two_with_equal_sums(const vector<ui_t> &ays,
                                      const ui_t ays_sum) {
    return ays_sum % 2ULL == 0ULL &&
           none_of(ays.cbegin(), ays.cend(),
                   [ays_sum](const ui_t a) { return a > ays_sum / 2ULL; });
}

int main() {
    ui_t n{0};
    cin >> n;

    vector<ui_t> ays(n);
    ui_t ays_sum{0ULL};

    for (auto &a : ays) {
        cin >> a;
        ays_sum += a;
    }

    cout << (can_split_in_two_with_equal_sums(ays, ays_sum) ? "YES" : "NO")
         << '\n';
    return 0;
}
