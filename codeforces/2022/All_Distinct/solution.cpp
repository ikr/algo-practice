#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int final_size(const vector<int> &xs) {
    map<int, int> fs;
    for (const auto x : xs) ++fs[x];

    priority_queue<int> ys;
    for (const auto [_, f] : fs) ys.push(f);

    int result{};

    while (!ys.empty()) {
        const auto a = ys.top();
        ys.pop();

        if (a == 1) {
            ++result;
        } else {
            if (ys.empty()) {
                result += (a % 2);
            } else {
                const auto b = ys.top();
                ys.pop();

                if (b == 1) {
                    result += (a % 2);
                    ys.push(b);
                } else {
                    if (a - 1 > 0) ys.push(a - 1);
                    if (b - 1 > 0) ys.push(b - 1);
                }
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << final_size(xs) << '\n';
    }

    return 0;
}
