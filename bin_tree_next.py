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
        return None

    def enumerate_paths(self, length):
        p =  [True] * length
        yield p
        while True in p:
            p = self.next_path(p)
            yield p

    def next_path(self, p):
        result = list(p)
        for i in range(len(result)):
            if result[i]:
                result[i] = False
                break
            result[i] = True
        return result

    def levels_count(self, root):
        result = 0
        n = root
        while n:
            result += 1
            n = n.left
        return result


s = Solution()
for p in s.enumerate_paths(5):
    print(p)
    p = s.next_path(p)
