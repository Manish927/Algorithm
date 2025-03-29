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
    
    def add_edge(self, vertex1, vertex2):
        if vertex1 in self.adjacency_list.keys() and vertex2 in self.adjacency_list.keys():
            self.adjacency_list[vertex1].append(vertex2)
            self.adjacency_list[vertex2].append(vertex1)
            return True
        
        return False

    def remove_edge(self, vertex1, vertex2):
        if vertex1 in self.adjacency_list.keys() and vertex2 in self.adjacency_list.keys():
            try:
                self.adjacency_list[vertex1].remove(vertex2)
                self.adjacency_list[vertex2].remove(vertex1)
            except ValueError:
                pass 

            return True
        return False

    def bfs(self, vertex):
        visited = set()
        visited.add(vertex)
        queue = deque([vertex])

        while queue:
            current_vertex = queue.popleft()
            print(current_vertex)
            for adjacent_vertex in self.adjacency_list[current_vertex]:
                if adjacent_vertex not in visited:
                    visited.add(adjacent_vertex)
                    queue.append(adjacent_vertex)


    def dfs(self, vertex):
        visisted = set()
        stack = [vertex]

        while stack:
            current_vertex = stack.pop()
            if current_vertex not in visisted:
                print(current_vertex)
                visisted.add(current_vertex)

            for adjacent_vertex in self.adjacency_list[current_vertex]:
                if adjacent_vertex not in visisted:
                    stack.append(adjacent_vertex)
                    


# Graph Algorithm, Topological sort, Dijkastra's algorithm, Bellman Ford algorithm, Floyd Warshall Algorithm

graph = Graph()
graph.add_vertex("A")
graph.add_vertex("B")
graph.add_vertex("C")
graph.add_vertex("D")
graph.add_vertex("E")
print(graph.adjacency_list)
graph.add_edge("A", "B")
graph.add_edge("A", "C")
graph.add_edge("B", "E")
graph.add_edge("C", "D")
graph.add_edge("D", "E")
# graph.remove_edge("A", "B")
print(graph.adjacency_list)
# graph.bfs("A")
graph.dfs("A")
