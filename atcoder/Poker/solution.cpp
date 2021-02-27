#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

int ten_pow(const int exp) {
    int ans = 1;
    for (int i = 1; i <= exp; ++i) ans *= 10;
    return ans;
}

int hand_score(const array<int, 5> &cs) {
    vector<int> fs(10, 0);
    for (const int c : cs) ++fs[c];

    int ans = 0;
    for (int i = 1; i <= 9; ++i) {
        ans += i * ten_pow(fs[i]);
    }
    return ans;
}

array<int, 5> potential_hand(const string &st, const int x) {
    return {st[0] - '0', st[1] - '0', st[2] - '0', st[3] - '0', x};
}

vector<int> freqs_of_already_dealt(const string &s, const string &t) {
    vector<int> ans(10, 0);
    for (int i = 0; i < 4; ++i) {
        ++ans[s[i] - '0'];
        ++ans[t[i] - '0'];
    }
    return ans;
}

double p_of_first_winning(const int k, const string &s, const string &t) {
    vector<int> score_a(10, 0);
    vector<int> score_b(10, 0);

    for (int i = 1; i <= 9; ++i) {
        score_a[i] = hand_score(potential_hand(s, i));
        score_b[i] = hand_score(potential_hand(t, i));
    }

    const auto dealt_fs = freqs_of_already_dealt(s, t);
    double ans = 0.0;
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            if (i == j && k - dealt_fs[i] < 2) continue;

            const double p1 = doof(k - dealt_fs[i]) / (9 * k - 8.0);
            const double p2 =
                doof(k - dealt_fs[j] - (i == j ? 1 : 0)) / (9 * k - 9.0);

            if (score_a[i] > score_b[j]) ans += p1 * p2;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int k;
    cin >> k;

    string s;
    string t;
    cin >> s >> t;

    cout << p_of_first_winning(k, s, t) << '\n';
    return 0;
}
