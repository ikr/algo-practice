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

    def reverse(self, head):
        new_head = None
        n = head
        while n:
            nn = n.next
            new_head = self.push(new_head, n)
            n = nn
        return new_head

    def push(self, head, n):
        if not head:
            n.next = None
            return n
        n.next = head
        return n


l2 = Node(2, Node(3, None))
l4 = Node(2, Node(3, Node(5, Node(7, None))))
l5 = Node(2, Node(3, Node(5, Node(7, Node(11, None)))))


def print_list(head):
    items = []
    n = head
    while n:
        items.append(str(n.val))
        n = n.next
    print('[' + ' '.join(items) + ']')


s = Solution()
print_list(s.reverse(l5))
