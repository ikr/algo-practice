class Node:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None


class Solution:
    # @param root, a tree node
    # @return nothing
    def connect(self, root):
        l = self.levels_count(root)
        for i in range(1, l):
            self.connect_recur(i, root, [])

    def connect_recur(self, distance, n, left_neigh_box):
        if distance == 0:
            if left_neigh_box:
                left_neigh_box[0].next = n
                left_neigh_box[0] = n
            else:
                left_neigh_box.append(n)
            return
        self.connect_recur(distance - 1, n.left, left_neigh_box)
        self.connect_recur(distance - 1, n.right, left_neigh_box)

    def levels_count(self, root):
        result = 0
        n = root
        while n:
            result += 1
            n = n.left
        return result


s = Solution()

n1 = Node(1)
n2 = Node(2)
n3 = Node(3)
n4 = Node(4)
n5 = Node(5)
n6 = Node(6)
n7 = Node(7)

n1.left = n2
n1.right = n5

n2.left = n3
n2.right = n4

n5.left = n6
n5.right = n7

s.connect(n1)
