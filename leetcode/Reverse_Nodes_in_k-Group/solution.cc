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
    ListNode *reverseKGroup(ListNode *head, int k) { return head; }

    ListNode *reverse(ListNode *head) {
        if (!head || !head->next)
            return head;

        ListNode *result = nullptr;
        auto a = head;
        auto b = a->next;
        auto c = b->next;

        while (true) {
            a->next = result;
            b->next = a;
            result = b;

            a = c;
            if (!a)
                break;

            b = a->next;
            if (!b) {
                a->next = result;
                result = a;
                break;
            }

            c = b->next;
        }

        return result;
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
    auto l = Solution().reverse(make_list({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    cout << l << endl;
    delete_list(l);

    return 0;
}
