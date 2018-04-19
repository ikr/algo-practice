class Node:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None


class Solution:
    # @param root, a tree node
    # @return nothing
    def connect(self, r):
        if not r.left:
            return
        r.left.next = r.right
        connect(r.left)
        connect(r.right)

    def level(self, node, distance, memo):
        if distance == 0:
            memo.append(node)
            return
        self.level(node.left, distance - 1, memo)
        self.level(node.right, distance - 1, memo)

    def levels_count(self, root):
        result = 0
        n = root
        while n:
            result += 1
            n = n.left
        return result
