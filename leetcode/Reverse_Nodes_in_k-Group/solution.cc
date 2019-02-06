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
        auto seek_res = seek(h, k);
        auto t = seek_res.first;
        auto gsize = seek_res.second;

        if (gsize < k)
            return h;

        auto p = t->next;
        t->next = nullptr;
        reverse(h);

        h->next = reverseKGroup(p, k);

        return t;
    }

  private:
    static pair<ListNode *, int> seek(ListNode *head, int k) {
        assert(head);
        auto p = head;
        auto countdown = k;

        while (--countdown && p->next) {
            p = p->next;
        }

        return make_pair(p, k - countdown);
    }

    static void reverse(ListNode *head) {
        if (!head || !head->next)
            return;

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
    auto l = Solution().reverseKGroup(make_list({1, 2, 3, 4, 5, 6, 7, 8, 9}), 4);
    cout << l << endl;
    delete_list(l);

    return 0;
}
