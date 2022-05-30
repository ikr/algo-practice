#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

priority_queue<int> freqs_seq(const vector<int> &xs) {
    int cur = -1;
    int num = 0;
    priority_queue<int> result;

    for (const auto x : xs) {
        if (cur == -1) {
            cur = x;
            num = 1;
        } else {
            if (cur == x) {
                ++num;
            } else {
                assert(num > 0);
                result.push(num % 2 ? 1 : 2);
                cur = x;
                num = 1;
            }
        }
    }

    assert(num > 0);
    result.push(num % 2 ? 1 : 2);
    return result;
}

int max_size(const vector<int> &xs) {
    auto fs = freqs_seq(xs);

    while (fs.top() > 1) {
        const auto a = fs.top();
        fs.pop();
        assert(!fs.empty());

        const auto b = fs.top();
        fs.pop();

        if (b == 1) {
            fs.push(a - 1);
        } else {
            assert(b == 2);

            fs.push(1);
            fs.push(1);
        }
    }

    return sz(fs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    cout << max_size(xs) << '\n';
    return 0;
}
