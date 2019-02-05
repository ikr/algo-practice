#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
  public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        return head;
    }
};

ListNode *make_list(const vector<int> xs) {
    ListNode *head = nullptr;
    ListNode *tail = nullptr;

    for (auto x : xs) {
        auto n = new ListNode(x);

        if (tail == nullptr) {
            head = n;
            tail = n;
            continue;
        }

        tail->next = n;
        tail = n;
    }

    return head;
}

void delete_list(ListNode *head) {
    auto p = head;

    while (p != nullptr) {
        auto current = p;
        p = p->next;
        delete current;
    }
}

ostream &operator<<(ostream &os, ListNode *head) {
    auto p = head;
    while (p != nullptr) {
        os << p->val << ' ';
        p = p->next;
    }

    return os;
}

int main() {
    auto l = Solution().reverseKGroup(make_list({1, 2, 3, 4, 5, 6, 7}), 2);
    cout << l << endl;
    delete_list(l);


    return 0;
}
