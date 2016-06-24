class BusinessTasks:
    def getTask(self, lst, n):
        return ''

def move_cursor(ringList, cursor, moves):
    remainder = moves % len(ringList)

    while remainder > 0:
        remainder -= 1
        cursor += 1
        if cursor == len(ringList):
            cursor = 0

    return cursor

print(move_cursor([1, 2, 3], 0, 8))
