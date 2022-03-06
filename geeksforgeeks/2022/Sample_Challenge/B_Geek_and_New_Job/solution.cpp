#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

function<bool(char)> make_range_indicator(const char lo, const char hi) {
    return [lo, hi](const char x) -> bool {
        return inof(lo) <= inof(x) && inof(x) <= inof(hi);
    };
}

static const auto is_lo_alpha = make_range_indicator('a', 'z');
static const auto is_up_alpha = make_range_indicator('A', 'Z');
static const auto is_digit = make_range_indicator('0', '9');

bool is_ok(const string &xs) {
    for (const auto ind : {is_lo_alpha, is_up_alpha, is_digit}) {
        if (none_of(cbegin(xs), cend(xs), ind)) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;
        cout << (is_ok(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
