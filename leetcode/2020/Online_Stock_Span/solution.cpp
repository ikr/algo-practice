struct StockSpanner final {
    StockSpanner() {}
    
    int next(const int price) {
        m_prices.push_back(price);
        
        while (
            !m_dominant_indices.empty() && 
            m_prices[m_dominant_indices.top()] <= price
        ) {
            m_dominant_indices.pop();
        }
        
        const int last_idx = m_prices.size() - 1;
        
        const int ans = (
            m_dominant_indices.empty() ? 
            last_idx + 1 : 
            last_idx - m_dominant_indices.top()
        );
        
        m_dominant_indices.push(last_idx);
        return ans;
    }
    
private:
    vector<int> m_prices;
    stack<int> m_dominant_indices;
};
