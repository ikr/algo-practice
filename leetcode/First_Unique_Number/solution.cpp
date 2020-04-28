#include <bits/stdc++.h>

using namespace std;

namespace {
using Iter = list<int>::const_iterator;
using Count = int;
using State = pair<Count, Iter>;
}

struct FirstUnique final {
    FirstUnique(const vector<int> &xs) {
        for (const int x : xs) add(x);
    }
    
    int showFirstUnique() const {
        return m_unique_xs_order.empty() ? -1 : m_unique_xs_order.front();
    }
    
    void add(const int x) {
        if (m_states_by_x.count(x)) {
            m_states_by_x[x].first++;
            
            if (m_states_by_x[x].second != m_unique_xs_order.cend()) {
                m_unique_xs_order.erase(m_states_by_x[x].second);
                m_states_by_x[x].second = m_unique_xs_order.cend();
            }
        } else {
            m_unique_xs_order.push_back(x);
            m_states_by_x[x] = State{1, --m_unique_xs_order.end()};
        }
    }
    
private:
    list<int> m_unique_xs_order;
    unordered_map<int, State> m_states_by_x;
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
