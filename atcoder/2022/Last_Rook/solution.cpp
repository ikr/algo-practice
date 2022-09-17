#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int query(const pii dro, const pii dco) {
    cout << "? " << dro.first << ' ' << dro.second << ' ' << dco.first << ' '
         << dco.second << endl;

    int result;
    cin >> result;
    return result;
}

void answer(const pii roco) {
    cout << "! " << roco.first << ' ' << roco.second << endl;
}

void interact(const int N) {
    int ro_lo = 1, ro_hi = N;

    while (ro_lo != ro_hi) {
        const auto mid = [&]() -> int {
            if (ro_lo + 1 == ro_hi) {
                return ro_lo;
            } else {
                return ro_lo + (ro_hi - ro_lo) / 2;
            }
        }();

        const auto res = query({ro_lo, mid}, {1, N});
        if (res != mid - ro_lo + 1) {
            ro_hi = mid;
        } else {
            ro_lo = mid + 1;
        }
    }

    int co_lo = 1, co_hi = N;

    while (co_lo != co_hi) {
        const auto mid = [&]() -> int {
            if (co_lo + 1 == co_hi) {
                return co_lo;
            } else {
                return co_lo + (co_hi - co_lo) / 2;
            }
        }();

        const auto res = query({1, N}, {co_lo, mid});
        if (res != mid - co_lo + 1) {
            co_hi = mid;
        } else {
            co_lo = mid + 1;
        }
    }

    answer({ro_lo, co_lo});
}

int main() {
    int N;
    cin >> N;

    interact(N);
    return 0;
}
