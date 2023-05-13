#include <bits/stdc++.h>
using namespace std;

map<char, int> freqs(const string &xs) {
    map<char, int> ans;
    for (const auto x : xs) {
        if (x == '@') continue;
        ++ans[x];
    }
    return ans;
}

bool good_char(const char x) {
    return string{"atcoder"}.find(x) != string::npos;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    string ys;
    cin >> ys;

    const auto yes = [&]() -> bool {
        auto ax = count(cbegin(xs), cend(xs), '@');
        auto ay = count(cbegin(ys), cend(ys), '@');

        auto fx = freqs(xs);
        auto fy = freqs(ys);

        while (!fx.empty()) {
            const auto x = cbegin(fx)->first;
            const auto iy = fy.find(x);

            if (iy == cend(fy)) {
                if (!good_char(x) || ay < cbegin(fx)->second) return false;
                ay -= cbegin(fx)->second;
                fx.erase(cbegin(fx));
                continue;
            }

            if (cbegin(fx)->second == iy->second) {
                fx.erase(cbegin(fx));
                fy.erase(iy);
                continue;
            }

            if (!good_char(x)) return false;

            const auto d = abs(cbegin(fx)->second - iy->second);
            if (cbegin(fx)->second > iy->second) {
                if (ay < d) return false;
                ay -= d;
            } else {
                if (ax < d) return false;
                ax -= d;
            }

            fx.erase(cbegin(fx));
            fy.erase(iy);
        }

        while (!fy.empty()) {
            const auto y = cbegin(fy)->first;
            if (!good_char(y)) return false;
            if (ax < cbegin(fy)->second) return false;

            ax -= cbegin(fy)->second;
            fy.erase(cbegin(fy));
        }

        return ax == ay;
    }();

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
