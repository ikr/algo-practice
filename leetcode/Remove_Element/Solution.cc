#include <iostream>
#include <vector>

using std::cout;
using std::vector;

class Solution {
public:
  int removeElement(vector<int> &nums, int val) { return 0; }
};

int main() {
  Solution s;
  vector<int> v{3, 2, 2, 3};
  auto result = s.removeElement(v, 0);
  cout << result << "\n";

  for (auto i : v) {
    cout << i << " ";
  }

  cout << "\n";

  return 0;
}
