from collections import deque


class CaptureThemAll:
    def fastKnight(self, knight, rook, queen):
        G = {coord(knight): vertex(0, None)}
        Q = deque([coord(knight)])

        while len(Q) > 0:
            current = Q.popleft()
            for a in adjacent(current):
                if not a in G:
                    G[a] = vertex(G[current]['d'] + 1, current)
                    qrCapture = a == coord(rook) and is_ancestor(G, coord(queen), a)
                    rqCapture = a == coord(queen) and is_ancestor(G, coord(rook), a)
                    if qrCapture or rqCapture:
                        return G[a]['d']
                    Q.append(a)


def is_ancestor(G, candidateCoord, vertexCoord):
    if not vertexCoord in G or not G[vertexCoord]['p']:
        return False

    if G[vertexCoord]['p'] == candidateCoord:
        return True

    return is_ancestor(G, candidateCoord, G[vertexCoord]['p'])


def adjacent(coord):
    result = []

    for dx, dy in adjacent_deltas():
        x = coord[0] + dx
        y = coord[1] + dy

        if 0 <= x <= 7 and 0 <= x <= 7:
            result.append((x, y))

    return result


def adjacent_deltas():
    return ((-2, -1), (-2, 1), (2, -1), (2, 1), (-1, -2), (1, -2), (-1, 2), (1, 2))


def coord(position):
    return ord(position[0]) - ord('a'), int(position[1]) - 1


def vertex(distance, parentCoord):
    return {'d': distance, 'p': parentCoord}


cta = CaptureThemAll()
print(cta.fastKnight('a1', 'b3', 'c5'))
print(cta.fastKnight('b1', 'c3', 'a3'))
print(cta.fastKnight('a1', 'a2', 'b2'))
print(cta.fastKnight('a5', 'b7', 'e4'))
print(cta.fastKnight('h8', 'e2', 'd2'))
