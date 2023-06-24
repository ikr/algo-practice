#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string xs;
    cin >> xs;

    string ans;
    stack<char> st;

    const auto pump_out = [&]() {
        string buf;
        buf.reserve(st.size());

        while (!st.empty()) {
            const auto c = st.top();
            st.pop();
            buf += c;
        }

        reverse(begin(buf), end(buf));
        ans += buf;
    };

    const auto drop = [&]() {
        for (;;) {
            const auto c = st.top();
            st.pop();
            if (c == '(') return;
        }
    };

    for (const auto c : xs) {
        if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            if (st.empty()) {
                ans += c;
            } else {
                drop();
            }
        } else {
            if (st.empty()) {
                ans += c;
            } else {
                st.push(c);
            }
        }
    }

    pump_out();

    cout << ans << '\n';
    return 0;
}
