#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
  public:
    void nextPermutation(vector<int> &xs) {
        const int rotation_group_idx = first_asc_pair(xs);

        if (rotation_group_idx != -1) {
            const int tail_min_idx = min_idx(xs, rotation_group_idx + 1);
            swap(xs[rotation_group_idx], xs[tail_min_idx]);
        }

        sort_from(xs, rotation_group_idx + 1);
    }

  private:
    static int first_asc_pair(const vector<int> &xs) {
        if (xs.size() < 2)
            return -1;

        for (int i = xs.size() - 2; i != -1; --i)
            if (xs[i] < xs[i + 1])
                return i;

        return -1;
    }

    static int min_idx(const vector<int> &xs, const int starting_from) {
        int result = starting_from;

        for (int i = starting_from + 1; i != xs.size(); ++i)
            if (xs[i] < xs[result])
                result = i;

        return result;
    }

    static void sort_from(vector<int> &xs, int starting_from) {
        sort(xs.begin() + starting_from, xs.end());
    }
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    vector<int> xs{1, 2, 3, 4};

    do {
        cout << xs << endl;
        Solution().nextPermutation(xs);
    } while (xs != vector<int>{1, 2, 3, 4});

    return 0;
}
