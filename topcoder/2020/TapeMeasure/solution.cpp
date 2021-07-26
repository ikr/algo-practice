#include <bits/stdc++.h>
using namespace std;

struct TapeMeasure final {
    vector<string> draw(const int lo, const int hi) const {
        const int sz = (hi - lo) * 2 + 1;

        vector<string> ans(5, string(sz, '#'));

        for (int i = 1; i < sz; i += 2) {
            ans[1][i] = ' ';
        }

        ans[2] = string(sz, ' ');
        for (int i = ((5 - (lo % 5)) % 5) * 2; i < sz; i += 10) {
            ans[2][i] = '#';
        }

        ans[3] = string(sz, ' ');
        ans[4] = string(sz, ' ');

        const int ii = ((10 - (lo % 10)) % 10) * 2 - 20;
        const int xx = (lo % 10 == 0 ? lo : ((lo / 10) * 10 + 10)) - 10;
        const string ss = to_string(xx);
        const int sssz = ss.size();

        for (int j = 0; j < sssz; ++j) {
            if (ii + j < sz && ii + j >= 0) ans[4][ii + j] = ss[j];
        }

        for (int i = ((10 - (lo % 10)) % 10) * 2,
                 x = (lo % 10 == 0 ? lo : ((lo / 10) * 10 + 10));
             i < sz; i += 20, x += 10) {
            ans[3][i] = '#';

            const string s = to_string(x);
            const int ssz = s.size();
            for (int j = 0; i + j < sz && j < ssz; ++j) {
                ans[4][i + j] = s[j];
            }
        }

        return ans;
    }
};

int main() {
    for (const auto &row : TapeMeasure{}.draw(981, 990)) {
        cout << row << '\n';
    }

    return 0;
}
