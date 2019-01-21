#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  public:
  private:
    static const unordered_map<char, char> increments_by_char;

    static char inc(char x) { return 0; }
};

const unordered_map<char, char> Solution::increments_by_char{
    {'1', 'a'}, {'a', 'b'}, {'b', 'c'},

    {'2', 'd'}, {'d', 'e'}, {'e', 'f'},

    {'3', 'g'}, {'g', 'h'}, {'h', 'i'}};

int main() {
    Solution s;

    cout << '\n';

    return 0;
}
