#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> sequence_of_cylinder_heights(const vector<int> &xs) {
    int h{};
    vector<pair<int, int>> cyl;
    vector<int> result;
    result.reserve(sz(xs));

    for (const auto x : xs) {
        if (cyl.empty()) {
            assert(h == 0);
            cyl.emplace_back(1, x);
            h = 1;
        } else {
            auto &[k, v] = cyl.back();

            if (v == x) {
                if (k + 1 == x) {
                    h -= k;
                    cyl.pop_back();
                } else {
                    ++k;
                    ++h;
                }
            } else {
                cyl.emplace_back(1, x);
                ++h;
            }
        }

        result.push_back(h);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    for (const auto y : sequence_of_cylinder_heights(xs)) {
        cout << y << '\n';
    }
    return 0;
}
