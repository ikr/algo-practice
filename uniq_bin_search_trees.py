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
        self.recur(A, -1, [], list(range(1, A + 1)), [], result)
        return list(map(lambda d: self.build_tree(A, d), result))

    def recur(self, total_nodes, n, xs_l, xs_r, desc, memo):
        if len(desc) == total_nodes and (not memo or (tuple(desc) != memo[-1])):
            memo.append(tuple(desc))
            return
        if not desc:
            for i in range(len(xs_r)):
                o = xs_r[i]
                self.recur(total_nodes, o, xs_r[0:i], xs_r[i + 1:], [o], memo)
            return
        if xs_l and not xs_r:
            for i in range(len(xs_l)):
                l = xs_l[i]
                desc_prime = list(desc)
                desc_prime.append((n, 'L', l))
                self.recur(total_nodes, l, xs_l[0:i], xs_l[i + 1:], desc_prime, memo)
        if xs_r and not xs_l:
            for i in range(len(xs_r)):
                r = xs_r[i]
                desc_prime = list(desc)
                desc_prime.append((n, 'R', r))
                self.recur(total_nodes, r, xs_r[0:i], xs_r[i + 1:], desc_prime, memo)
        if xs_l and xs_r:
            for i in range(len(xs_l)):
                for j in range(len(xs_r)):
                    l = xs_l[i]
                    r = xs_r[j]
                    desc_prime = list(desc)
                    desc_prime.append((n, 'L', l))
                    desc_prime.append((n, 'R', r))
                    self.recur(total_nodes, l, xs_l[0:i], xs_l[i + 1:], desc_prime, memo)
                    self.recur(total_nodes, r, xs_r[0:j], xs_r[j + 1:], desc_prime, memo)

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


s = Solution()
descs = []
s.recur(3, -1, [], list(range(1, 3 + 1)), [], descs)

for d in descs:
    print(d)

print

print_trees(s.generateTrees(3))
