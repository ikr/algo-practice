#include <bits/stdc++.h>
using namespace std;

template <typename T> string join(const string &glue, const vector<T> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += to_string(t);
    }

    return ans;
}

using vi = vector<int>;

void print_tree(const vi &xs) {
    stack<vi> st;
    const auto print_top = [&st]() { cout << join(".", st.top()) << '\n'; };

    for (const auto x : xs) {
        if (st.empty()) {
            cout << "1\n";
            st.push(vi{1});
            continue;
        }

        if (x == 1) {
            vi path = st.top();
            path.push_back(1);
            st.push(path);

            print_top();
            continue;
        }

        while (st.top().back() != x - 1) st.pop();

        st.top().back() = x;
        print_top();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        print_tree(xs);
    }

    return 0;
}
