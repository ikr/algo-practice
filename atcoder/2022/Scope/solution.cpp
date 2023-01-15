#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_lo_letter(const char x) {
    return inof('a') <= inof(x) && inof(x) <= inof('z');
}

bool can_finish(const string &xs) {
    set<char> box;
    stack<set<char>> st;
    set<char> cur;

    for (const auto x : xs) {
        if (x == '(') {
            st.push(cur);
            cur.clear();
        } else if (x == ')') {
            for (const auto c : cur) box.erase(c);

            assert(!st.empty());
            cur = st.top();
            st.pop();
        } else {
            assert(is_lo_letter(x));
            if (box.count(x)) return false;
            cur.insert(x);
            box.insert(x);
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    cout << (can_finish(xs) ? "Yes" : "No") << '\n';
    return 0;
}
