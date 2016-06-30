from collections import deque


class CaptureThemAll:
    def fastKnight(self, knight, rook, queen):
        rq = min_moves(coord(knight), coord(rook)) + min_moves(coord(rook), coord(queen))
        qr = min_moves(coord(knight), coord(queen)) + min_moves(coord(queen), coord(rook))
        return min(rq, qr)


def min_moves(srcCoord, destCoord):
    M = {srcCoord: 0}
    P = {srcCoord: None}
    Q = deque([srcCoord])

    while len(Q) > 0:
        current = Q.popleft()
        for a in adjacent(current):
            if not a in M:
                M[a] = M[current] + 1
                P[a] = current
                if a == destCoord:
                    print(path(P, current, []))
                    return M[a]
                Q.append(a)


def path(P, a, agg):
    if not a:
        return agg

    agg.insert(0, a)
    return path(P, P[a], agg)



def adjacent(coord):
    result = []

    for dx, dy in adjacent_deltas():
        x = coord[0] + dx
        y = coord[1] + dy

        if 0 <= x <= 7 and 0 <= y <= 7:
            result.append((x, y))

    return result


def adjacent_deltas():
    return ((-2, -1), (-2, 1), (2, -1), (2, 1), (-1, -2), (1, -2), (-1, 2), (1, 2))


def coord(position):
    return ord(position[0]) - ord('a'), int(position[1]) - 1


cta = CaptureThemAll()
# print(cta.fastKnight('a1', 'b3', 'c5'))
# print(cta.fastKnight('b1', 'c3', 'a3'))
print(cta.fastKnight('a1', 'a2', 'b2'))
# print(cta.fastKnight('a5', 'b7', 'e4'))
# print(cta.fastKnight('h8', 'e2', 'd2'))
