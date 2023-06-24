#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void paste(vector<string> &canvas, const vector<string> &what,
           const int offset_ro, const int offset_co) {
    const auto H = sz(what);
    const auto W = sz(what[0]);

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (what[ro][co] == '#') {
                canvas[offset_ro + ro][offset_co + co] = '#';
            }
        }
    }
}

vector<string> cut_by_blacks(const vector<string> &canvas) {
    const auto H = sz(canvas);
    const auto W = sz(canvas[0]);

    int ro_lo = H - 1, ro_hi = 0, co_lo = W - 1, co_hi = 0;
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (canvas[ro][co] == '#') {
                ro_lo = min(ro_lo, ro);
                ro_hi = max(ro_hi, ro);
                co_lo = min(co_lo, co);
                co_hi = max(co_hi, co);
            }
        }
    }

    vector<string> result(ro_hi - ro_lo + 1, string(co_hi - co_lo + 1, '.'));
    for (int ro = 0; ro < sz(result); ++ro) {
        for (int co = 0; co < sz(result[0]); ++co) {
            result[ro][co] = canvas[ro_lo + ro][co_lo + co];
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int HA, WA;
    cin >> HA >> WA;
    vector<string> ga(HA);
    for (auto &row : ga) {
        cin >> row;
        assert(sz(row) == WA);
    }

    int HB, WB;
    cin >> HB >> WB;
    vector<string> gb(HB);
    for (auto &row : gb) {
        cin >> row;
        assert(sz(row) == WB);
    }

    int HX, WX;
    cin >> HX >> WX;
    vector<string> gx(HX);
    for (auto &row : gx) {
        cin >> row;
        assert(sz(row) == WX);
    }

    const auto gxx = cut_by_blacks(gx);

    const auto yes = [&]() -> bool {
        for (int aro = 0; aro < 20 - HA; ++aro) {
            for (int aco = 0; aco < 20 - WA; ++aco) {
                for (int bro = 0; bro < 20 - HB; ++bro) {
                    for (int bco = 0; bco < 20 - WB; ++bco) {
                        vector<string> canvas(20, string(20, '.'));

                        paste(canvas, ga, aro, aco);
                        paste(canvas, gb, bro, bco);

                        if (cut_by_blacks(canvas) == gxx) return true;
                    }
                }
            }
        }

        return false;
    }();

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
