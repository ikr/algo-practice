#include <iostream>
#include <vector>

using std::cout;
using std::vector;

class Solution {
   public:
    int removeElement(vector<int> &nums, int val) {
        int length = 0;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == val) continue;

            nums[length] = nums[i];
            if (length != i) nums[i] = val;

            ++length;
        }

        return length;
    }
};

int main() {
    Solution s;
    vector<int> v{0, 1, 2, 2, 3, 0, 4, 2};

    int result = s.removeElement(v, 2);
    cout << result << "\n";

    for (auto i : v) {
        cout << i << " ";
    }

    cout << "\n";

    return 0;
}
