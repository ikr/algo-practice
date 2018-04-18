class Solution:
    # @param A : list of integers
    # @return a list of list of integers
    def permute(self, A):
        memo = set()
        self.recur([], A, memo)
        return list(memo)

    def recur(self, prefix, xs, memo):
        if not xs:
            memo.add(tuple(prefix))
            return
        for i in range(len(xs)):
            new_prefix = list(prefix)
            new_prefix.append(xs[i])
            self.recur(new_prefix, xs[0:i] + xs[i+1:], memo)

s = Solution()
ps = s.permute([1, 1, 2, 2, 3, 3])
for p in ps:
    print(p)
