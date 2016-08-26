class TurntableService:
    def calculateTime(favorites):
        return -1


def turn_left(ttable):
    return ttable[1:] + ttable[0:1]


def turn_right(ttable):
    return (ttable[-1],) + ttable[0:-1]


tt = (2, 3, 5, 7, 11)

print(turn_left(tt))
print(turn_right(tt))
