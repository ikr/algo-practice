#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool operator<(const ListNode &n1, const ListNode &n2) {
    return n1.val < n2.val;
}

class Solution {
  public:
    ListNode *mergeKLists(vector<ListNode *> &lists) { return nullptr; }
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

void println(ListNode *head) {
    auto p = head;
    while (p != nullptr) {
        cout << p->val << ' ';
        p = p->next;
    }
    cout << endl;
}

int main() {
    Solution s;

    cout << endl;

    return 0;
}
