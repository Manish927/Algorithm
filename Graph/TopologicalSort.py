from collections import deque

class Graph:
    def __init__(self):
        # {'A': ['B', 'C'], 'B': ['A', 'E'], 'C': ['A', 'D'], 'D': ['C', 'E'], 'E': ['B', 'D']}
        self.adjacency_list = {}

    def add_vertex(self, vertex):
        if vertex not in self.adjacency_list.keys():
            self.adjacency_list[vertex] = []
            return True
        
        return False

    # Topological sort works for directed graph, hence we need to change the add_edge method
    def add_edge(self, vertex1, vertex2):
        if vertex1 in self.adjacency_list.keys():
            self.adjacency_list[vertex1].append(vertex2)
            if vertex2 not in self.adjacency_list:
                self.adjacency_list[vertex1] = []

    def remove_edge(self, vertex1, vertex2):
        if vertex1 in self.adjacency_list.keys() and vertex2 in self.adjacency_list.keys():
            try:
                self.adjacency_list[vertex1].remove(vertex2)
                self.adjacency_list[vertex2].remove(vertex1)
            except ValueError:
                pass 

            return True
        return False

    def topological_sort(self):
        visited = set()
        stack = []

        for vertex in self.adjacency_list:
            if vertex not in visited:
                self.topological_sort_util(vertex, visited, stack)

        return stack

    def topological_sort_util(self, vertex, visisted, stack):
        visisted.add(vertex)

        for neighbour in self.adjacency_list[vertex]:
            if neighbour not in visisted:
                self.topological_sort_util(neighbour, visisted, stack)

        stack.insert(0, vertex)

# Graph Algorithm, Topological sort, Dijkastra's algorithm, Bellman Ford algorithm, Floyd Warshall Algorithm

graph = Graph()
graph.add_vertex("A")
graph.add_vertex("B")
graph.add_vertex("C")
graph.add_vertex("D")
graph.add_vertex("E")
graph.add_vertex("F")
graph.add_vertex("G")
graph.add_vertex("H")

graph.add_edge("A", "C")
graph.add_edge("C", "E")
graph.add_edge("E", "H")
graph.add_edge("E", "F")
graph.add_edge("F", "G")
graph.add_edge("B", "C")
graph.add_edge("B", "D")
graph.add_edge("D", "F")

print(graph.adjacency_list)
print(graph.topological_sort())
