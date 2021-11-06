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

class CompareHeads {
  public:
    bool operator()(ListNode *n1, ListNode *n2) const {
        if (n1 == nullptr && n2 == nullptr)
            return false;

        if (n1 == nullptr)
            return true;

        if (n2 == nullptr)
            return false;

        return n1->val > n2->val;
    }
};

class Solution {
  public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        remove_empty(lists);

        make_heap(lists.begin(), lists.end(), CompareHeads());
        ListNode *head = nullptr;
        ListNode *tail = nullptr;

        while (!lists.empty()) {
            pop_heap(lists.begin(), lists.end(), CompareHeads());
            auto minimal = lists.back();
            lists.pop_back();

            auto new_head = minimal->next;
            head = chain_in(head, tail, minimal);
            tail = minimal;

            if (new_head != nullptr) {
                lists.push_back(new_head);
                push_heap(lists.begin(), lists.end(), CompareHeads());
            }
        }

        return head;
    }

  private:
    static void remove_empty(vector<ListNode *> &lists) {
        for (auto i = lists.begin(); i != lists.end();) {
            if (*i == nullptr) {
                i = lists.erase(i);
            } else {
                ++i;
            }
        }
    }

    static ListNode *chain_in(ListNode *head, ListNode *tail,
                              ListNode *new_node) {
        new_node->next = nullptr;

        if (tail == nullptr)
            return new_node;

        tail->next = new_node;
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
    auto l1 = make_list({1, 4, 5});
    auto l2 = make_list({1, 3, 4});
    auto l3 = make_list({2, 6});
    vector<ListNode *> v{l1, l2, l3, nullptr};
    auto result = s.mergeKLists(v);
    println(result);

    delete_list(result);

    return 0;
}
