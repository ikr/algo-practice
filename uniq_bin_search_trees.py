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
        self.recur(-1, list(range(1, A + 1)), [], [], result)
        return result

    def recur(self, n, xs_l, xs_r, desc, memo):
        if not xs_l and not xs_r:
            memo.append(desc)
            return
        if not desc:
            for i in range(len(xs_l)):
                o = xs_l[i]
                self.recur(o, xs_l[0:i], xs_l[i + 1:], [o], memo)
            return
        if xs_l:
            for i in range(len(xs_l)):
                l = xs_l[i]
                desc_prime = list(desc)
                desc_prime.append((n, 'L', l))
                self.recur(l, xs_l[0:i], xs_l[i + 1:], desc_prime, memo)
        if xs_r:
            for i in range(len(xs_r)):
                r = xs_r[i]
                desc_prime = list(desc)
                desc_prime.append((n, 'R', r))
                self.recur(r, xs_r[0:i], xs_r[i + 1:], desc_prime, memo)

    def build_tree(self, nodes_count, desc):
        nodes = map(TreeNode, range(1, nodes_count + 1))
        for i in range(1, len(desc)):
            p, b, c = desc[i]
            if b == 'L':
                nodes[p - 1].left = nodes[c - 1]
            else:
                nodes[p - 1].right = nodes[c - 1]
        return nodes[desc[0] - 1]


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
n1.right = n2
n2.right = n3

s = Solution()
print_trees([n1])
print_trees([s.build_tree(3, (1, (1, 'R', 2), (2, 'R', 3)))])

print

for d in s.generateTrees(3):
    print(d)
