#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
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

class Solution {
  public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *pre_p1 = nullptr;
        auto p1 = head;
        auto p2 = head;
        auto seek = n;

        while (seek--) {
            if (p2 == nullptr) {
                return head;
            }
            p2 = p2->next;
        }

        while (p2 != nullptr) {
            pre_p1 = p1;
            p1 = p1->next;
            p2 = p2->next;
        }

        if (p1 == head) {
            auto result = p1->next;
            delete p1;
            return result;
        } else {
            delete_next(pre_p1);
            return head;
        }
    }

  private:
    void delete_next(ListNode *n) {
        ListNode *m = n->next;

        if (m == nullptr) {
            return;
        }

        n->next = m->next;
        delete m;
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

    auto head = make_list({1, 2, 3, 4, 5, 6});
    println(head);
    head = s.removeNthFromEnd(head, 4);
    println(head);
    delete_list(head);

    return 0;
}
