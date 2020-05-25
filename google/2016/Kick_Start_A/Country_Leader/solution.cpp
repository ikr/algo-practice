#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using si = set<int>;
using usi = unordered_set<int>;
using vll = vector<ll>;
using vd = vector<double>;
using vs = vector<string>;
static const ll M = 1e9 + 7;
template <typename T> constexpr int intof(const T x) { return static_cast<int>(x); }

int letter_count(const string &s) {
    unordered_set<char> letters(s.cbegin(), s.cend());
    letters.erase(' ');
    return letters.size();
}

string solve(const vs &ns) {
    return *max_element(
        ns.cbegin(), 
        ns.cend(),
        [](const auto &lhs, const auto &rhs) {
            if (letter_count(lhs) == letter_count(rhs)) {
                return lhs > rhs;
            }
            
            return letter_count(lhs) < letter_count(rhs);
        }
    );
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        int N;
        cin >> N;
        string buf;
        getline(cin, buf);
        
        vs names(N, "");
        for (auto &name : names) {
            getline(cin, name);
        }
        
        cout << "Case #" << i << ": " << solve(names) << '\n';
    }

    return 0;
}
