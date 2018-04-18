from heapq import *

class Solution:
    # @param A : tuple of integers
    # @param B : integer
    # @return an integer
    def kthsmallest(self, A, B):
        h = []
        for x in A:
            if len(h) < B:
                heappush(h, -x)
            else:
                if -h[0] > x:
                    heappop(h)
                    heappush(h, -x)
        return -h[0]


s = Solution()
print(s.kthsmallest((1, 4, 3, 2, 12, 34, 4, 5, 6, 7, 78, 8, 2, 1, 6, 7, 8), 5))
