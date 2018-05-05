#!/usr/bin/env python3

from collections import deque

def roadsAndLibraries(n, c_lib, c_road, cities):
    graph = init_graph(n, cities)
    components = deque()
    for i in range(1, n + 1):
        if i not in graph:
            continue
        component_root = graph[i]
        connect(graph, component_root)
        components.append(component_root)
    return sum(map(lambda c: min_cost(c_lib, c_road, c), components))

def connect(graph, root):
    del graph[root.id]
    for neigh in root.neighs:
        if neigh.id in graph:
            connect(graph, neigh)

def min_cost(c_lib, c_road, root):
    cities, roads = cities_and_roads(root, 0, 0)
    return min(cities * c_lib, c_lib + roads * c_road)

def cities_and_roads(root, cities, roads):
    root.counted = True
    cities += 1
    for neigh in root.neighs:
        if not neigh.counted:
            cities, roads = cities_and_roads(neigh, cities, roads + 1)
    return cities, roads

def init_graph(n, cities):
    nodes = dict(map(lambda x: (x, Node(x)), range(1, n + 1)))
    for id1, id2 in cities:
        nodes[id1].neighs.append(nodes[id2])
        nodes[id2].neighs.append(nodes[id1])
    return nodes

class Node:
    def __init__(self, id):
        self.id = id
        self.neighs = []
        self.counted = False

if __name__ == "__main__":
    q = int(input().strip())
    for a0 in range(q):
        n, m, c_lib, c_road = input().strip().split(' ')
        n, m, c_lib, c_road = [int(n), int(m), int(c_lib), int(c_road)]
        cities = []
        for cities_i in range(m):
           cities_t = [int(cities_temp) for cities_temp in input().strip().split(' ')]
           cities.append(cities_t)
        result = roadsAndLibraries(n, c_lib, c_road, cities)
        print(result)
