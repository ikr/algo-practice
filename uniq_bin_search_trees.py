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
        self.recur(None, None, list(range(1, A + 1)), [], result)
        print
        return result

    def recur(self, root, n, xs_l, xs_r, memo):
        print(root.val if root else '-', xs_l, xs_r, n.val if n else '-')
        if not xs_l and not xs_r:
            memo.append(root)
            print_trees([root])
            return
        if not root:
            for i in range(len(xs_l)):
                o = TreeNode(xs_l[i])
                self.recur(o, o, xs_l[0:i], xs_l[i + 1:], memo)
            return
        if xs_l:
            for i in range(len(xs_l)):
                l = TreeNode(xs_l[i])
                n.left = l
                self.recur(root, l, xs_l[0:i], xs_l[i + 1:], memo)
        if xs_r:
            for i in range(len(xs_r)):
                r = TreeNode(xs_r[i])
                n.right = r
                self.recur(root, r, xs_r[0:i], xs_r[i + 1:], memo)


def traverse(root, memo):
    if not root:
        return
    traverse(root.left, memo)
    traverse(root.right, memo)
    memo.append(root.val)

def print_trees(ts):
    for root in ts:
        memo = []
        traverse(root, memo)
        print(memo)


n1 = TreeNode(1)
n2 = TreeNode(2)
n3 = TreeNode(3)
n1.left = n2
n1.right = n3

s = Solution()
print_trees([n1])
print
print_trees(s.generateTrees(3))
