class Node:
    def __init__(self, val, next):
        self.val = val
        self.next = next

class Solution:
    # @param A : head node of linked list
    # @return the head node in the linked list
    def subtract(self, A):
        l = self.length(A)
        if l == 1:
            return A
        mid_next = self.move_to_mid_next(l, A)
        n = A
        for i in range(l // 2):
            m = self.move_forward(mid_next, l // 2 - i - 1)
            n.val = m.val - n.val
            n = n.next
        return A

    def move_to_mid_next(self, length, head):
        return self.move_forward(head, length // 2 + (0 if length % 2 == 0 else 1))

    def length(self, head):
        if not head:
            return 0
        result = 0
        n = head
        while n:
            result += 1
            n = n.next
        return result

    def move_forward(self, n, steps):
        for _ in range(steps):
            n = n.next
        return n

s = Solution()
print(s.move_to_mid_next(2, Node(2, Node(3, None))).val)
print(s.move_to_mid_next(4, Node(2, Node(3, Node(5, Node(7, None))))).val)
print(s.move_to_mid_next(5, Node(2, Node(3, Node(5, Node(7, Node(11, None)))))).val)
print(s.subtract(Node(2, Node(3, Node(5, Node(7, Node(11, None)))))).val)
