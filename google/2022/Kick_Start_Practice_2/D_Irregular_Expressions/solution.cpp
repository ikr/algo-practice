#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int is_vowel(const char x) {
    switch (x) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;

    default:
        return false;
    }
}

vector<int> vowels_num_prefix_sums(const string &xs) {
    vector<int> result(sz(xs), 0);
    result[0] = is_vowel(xs[0]);

    for (int i = 1; i < sz(xs); ++i) {
        result[i] = result[i - 1];
        if (is_vowel(xs[i])) ++result[i];
    }

    return result;
}

bool search_spell_by_first_word(const string &xs,
                                const function<int(int, int)> vowels_num,
                                const int l, const int r) {
    const auto k = r - l + 1;
    const auto i = xs.rfind(xs.substr(l, k));
    assert(i != xs.npos);
    if (inof(i) <= r + 1) return false;
    return vowels_num(r + 1, inof(i) - 1) > 0;
}

bool is_spell(const string &xs) {
    const auto pref = vowels_num_prefix_sums(xs);
    const auto vowels_num = [&pref](const int l, const int r) -> int {
        return pref[r] - (l ? pref[l - 1] : 0);
    };

    for (int i = 0; i + 5 <= sz(xs); ++i) {
        for (int j = i + 1; j < sz(xs); ++j) {
            const auto k = j - i + 1;
            if (j + 2 + k > sz(xs)) break;
            if (vowels_num(i, j) < 2) continue;
            if (search_spell_by_first_word(xs, vowels_num, i, j)) return true;
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string xs;
        cin >> xs;

        cout << "Case #" << i << ": " << (is_spell(xs) ? "Spell!" : "Nothing.")
             << '\n';
    }

    return 0;
}
