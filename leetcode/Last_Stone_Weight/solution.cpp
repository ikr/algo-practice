int pop(vector<int> &heap) {
    pop_heap(heap.begin(), heap.end());
    const int ans = heap.back();
    heap.pop_back();
    return ans;
}

class Solution {
public:
    int lastStoneWeight(vector<int> xs) {
        make_heap(xs.begin(), xs.end());
        
        while (xs.size() > 1) {
            const int y = pop(xs);
            const int x = pop(xs);
            
            if (y > x) {
                xs.push_back(y - x);
                push_heap(xs.begin(), xs.end());
            }
        }
        
        return xs.empty() ? 0 : xs.back();
    }
};
