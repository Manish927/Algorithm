
class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def add_edge(self, s, d, w):
        self.graph.append([s, d, w])

    def print_solution(self, dist):
        print("Vertex distance from Source")

        for vertex in self.V:
            print(f'{vertex}: {dist[vertex]}')

    def bellmamFord(self, src):
        dist = {vertex: float("Inf") for vertex in self.V}
        dist[src] = 0

        for _ in range(len(self.V) - 1):
            for s, d, w in self.graph:
                if dist[s] != float("Inf") and dist[s] + w < dist[d]:
                    dist[d] = dist[s] + w

        # run one more time for negative weight
        for s, d, w in self.graph:
            if dist[s] != float("Inf") and dist[s] + w < dist[d]:
                print("Graph contains negative cycle")
                return
        self.print_solution(dist) 
            


vertices = ["A", "B", "C", "D", "E"]
g = Graph(vertices)

g.add_edge("A", "C", 6)
g.add_edge("A", "D", 6)
# g.add_edge("A", "D", -6) for negative cycle
g.add_edge("B", "A", 3)
g.add_edge("C", "D", 1)
g.add_edge("D", "C", 2)
g.add_edge("D", "B", 1)
g.add_edge("E", "B", 4)
g.add_edge("E", "D", 2)
g.bellmamFord("E")

# Output
# Vertex distance from Source
# A: 6
# B: 3
# C: 4
# D: 2
# E: 0

