class Graph:
    def __init__(self, num_vertices):
        self.num_vertices = num_vertices
        self.adjacency_mtx = [[0 for _ in range(num_vertices)] for _ in range(num_vertices)]

    def add_edge(self, vertex1_index, vertex2_index):

        if vertex1_index >= self.num_vertices or vertex2_index >= self.num_vertices:
             return False
        
        self.adjacency_mtx[vertex1_index][vertex2_index] = 1
        self.adjacency_mtx[vertex2_index][vertex1_index] = 1

        return True

    def remove_edge(self, vertex1_index, vertex2_index):
        if vertex1_index >= self.num_vertices or vertex2_index >= self.num_vertices:
             return False
        
        self.adjacency_mtx[vertex1_index][vertex2_index] = 0
        self.adjacency_mtx[vertex2_index][vertex1_index] = 0

graph = Graph(5)
graph.add_edge(8, 8)
graph.add_edge(0, 1)

print(graph.adjacency_mtx)
graph.remove_edge(0,1)
print(graph.adjacency_mtx)
