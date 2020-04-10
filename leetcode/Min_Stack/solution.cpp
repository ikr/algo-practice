class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(const int x) {
        const int latest_min = m_mins.empty() ? INT_MAX : m_mins.back();
        const int new_min = min(latest_min, x);
        
        m_xs.push_back(x);
        m_mins.push_back(new_min);
    }
    
    void pop() {
        m_xs.pop_back();
        m_mins.pop_back();
    }
    
    int top() {
        return m_xs.back();
    }
    
    int getMin() {
        return m_mins.back();
    }
        
private:
    vector<int> m_xs;
    vector<int> m_mins;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
