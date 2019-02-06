#include <algorithm>
#include <cassert>
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
        if (k < 2 || !head || !head->next)
            return head;

        auto h = head;
        head = nullptr;

        while (true) {
            auto t = seek(h, k);
            auto p = t->next;
            t->next = nullptr;

            reverse(h);
            if (!head)
                head = t;
        }

        return head;
    }

  private:
    static ListNode *seek(ListNode *head, int k) {
        assert(head);
        auto p = head;

        while (--k && p->next) {
            p = p->next;
        }

        return p;
    }

    static void reverse(ListNode *head) {
        if (!head || !head->next)
            return head;

        auto a = head;
        auto b = a->next;
        auto c = b->next;
        head = nullptr;

        while (true) {
            a->next = head;
            b->next = a;
            head = b;

            a = c;
            if (!a)
                break;

            b = a->next;
            if (!b) {
                a->next = head;
                head = a;
                break;
            }

            c = b->next;
        }
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
    auto l =
        Solution().reverseKGroup(make_list({1, 2, 3, 4, 5, 6, 7, 8, 9}), 1);
    cout << l << endl;
    delete_list(l);

    return 0;
}
