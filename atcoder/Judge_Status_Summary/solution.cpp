#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    vector<string> ss(t, "");
    for (auto &s : ss) cin >> s;

    unordered_map<string, int> cnt;
    for (const auto &s : ss) {
        ++cnt[s];
    }

    cout << "AC x " << cnt["AC"] << '\n';
    cout << "WA x " << cnt["WA"] << '\n';
    cout << "TLE x " << cnt["TLE"] << '\n';
    cout << "RE x " << cnt["RE"] << '\n';

    return 0;
}
