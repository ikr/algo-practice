#!/usr/bin/env python3


class Node:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def mergeTwoLists(self, l1, l2):
        head = None
        tail = None
        n1 = l1
        n2 = l2
        while n1 or n2:
            if n1 and n2:
                smaller_n,  = (n1, n2) if n1.val < n2.val else (n2, n1)
                n1 = n1.next
                n2 = n2.next
                head, tail = self.append(head, tail, smaller_n)
                head, tail = self.append(head, tail, larger_n)
            elif n1:
                n = n1
                n1 = n1.next
                head, tail = self.append(head, tail, n)
            elif n2:
                n = n2
                n2 = n2.next
                head, tail = self.append(head, tail, n)
            tail.next = None
        return head

    def append(self, head, tail, node):
        if not tail:
            tail = node
            head = node
            return head, tail
        tail.next = node
        return head, node


if __name__ == '__main__':
    l11 = Node(1)
    l12 = Node(2)
    l11.next = l12
    l13 = Node(4)
    l12.next = l13

    l21 = Node(1)
    l22 = Node(3)
    l21.next = l22
    l23 = Node(4)
    l22.next = l23

    s = Solution()
    s.mergeTwoLists(l11, l12)
