class BusinessTasks:
    def getTask(self, tasks, n):
        return reduce_towards_one(list(tasks), 0, n - 1)[0]


def reduce_towards_one(ringList, cursor, moves):
    if len(ringList) == 1:
        return ringList

    c = move_cursor(ringList, cursor, moves)
    del ringList[c]
    if c == len(ringList):
        c = 0

    return reduce_towards_one(ringList, c, moves)


def move_cursor(ringList, cursor, moves):
    remainder = moves % len(ringList)

    while remainder > 0:
        remainder -= 1
        cursor += 1
        if cursor == len(ringList):
            cursor = 0

    return cursor
