
def floydwarshall(graph):
    V = len(graph)
    dist = graph

    for k in range(V):
        for i in range(V):
            for j in range(V):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist


INF = float("Inf")
graph = [
    [0, 5, INF, 1],
    [INF, 0, 1, INF],
    [4, INF, 0, INF],
    [INF, 2, 9, 0]
]

print(floydwarshall(graph))

# [[0, 3, 4, 1], [5, 0, 1, 6], [4, 7, 0, 5], [7, 2, 3, 0]]
