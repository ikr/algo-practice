class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    # @param A : integer
    # @return a list of TreeNode
    def generateTrees(self, A):
        result = []
        self.recur(None, list(range(1, A + 1)), [], result)
        return result

    def recur(self, root, xs_l, xs_r, memo):
        if not xs_l and not xs_r:
            memo.append(root)
            return
        if not root:
            for i in range(len(xs_l)):
                self.recur(TreeNode(xs_l[i]), xs_l[0:i], xs_l[i + 1:], memo)
            return
        if xs_l:
            for i in range(len(xs_l)):
                l = TreeNode(xs_l[i])
                root.left = l
                self.recur(l, xs_l[0:i], xs_l[i + 1:], memo)
        if xs_r:
            for i in range(len(xs_r)):
                r = TreeNode(xs_r[i])
                root.right = r
                self.recur(r, xs_r[0:i], xs_r[i + 1:], memo)


s = Solution()
print(s.generateTrees(3))
