Homework 7
==========
**Name:** Nick Palutsis  
**Date:** 28 November 2017

Problem 1
---------
My algorithm is based off of the greedy Dijkstra algorithm to find the single-source shortest path of a graph since the graph uses non-negative weights. Each vertex in the graph will store the shortest distance to reach that particular node from the origin node. Initially, this value for all of the nodes will be set to infinity. The distance value of the origin will be set to zero. Each vertex will also store a pointer to the previous vertex in the path, but it will initially be set to NULL. Each vertex will also store a boolean to keep track of whether the vertex has been visited. This is initially false. My algorithm will visit the unvisited vertex with the lowest distance value, v, and mark it as visited. Then, for each neighboring vertex, n, the minimum between n’s current value and the sum of v.distance and the weight of the edge between v and n. If a new value is stored, then a pointer to v is stored on n. This is repeated until the final vertex is visited or a path cannot be found. If a path is found, then the distance is printed out, the path is printed out, and the vertices are returned.

```
shortestPath(G, s, f):                      # graph, start, finish
    for v in G:
        vertices[v].distance = INFINITY     # set distances to infinity
        vertices[v].previous = NULL         # set pointer to previous vertex
        vertices[v].visited = False         # set vertices to unvisited

    vertices[s].distance = 0

    while True:
        current = NULL
        # find shortest unvisited vertex
        for v in G:
            if vertices[v].visited == False:
                if current == NULL:
                    current = vertices[v]
                if vertices[v].distance < current.distance:
                    current = vertices[v]

        if current == NULL:
            break                           # all vertices have been visited

        if current.distance == INFINITY:    # all connected vertices have been visited
            return "No path found"

        current.visited = True              # mark as visited

        for n in current:                   # for each neighbor of current, compute smallest dist
            if vertices[n].distance > current.distance + w(current, n):
                vertices[n].distance = current.distance + w(current, n)
                vertices[n].previous = n

        if current == vertices[f]:
            break

    print("The total distance is: " + vertices[f].distance)
    print("The shortest path is: ")
    current = f
    while True:
        print(current)
        if current.previous != NULL:
            current = current.previous
            print(", ")
        elif:
            break

    return vertices
```

My algorithm runs in `O(V^2)` complexity. This is because it takes `O(V)` to initialize the values of the graph. Identifying the smallest unvisited vertex takes `O(V)` since it checks each vertex once. Computing the new distances for the neighboring nodes takes `O(E)` complexity since at most each edge will be visited once. All of this happens at most `V` times which adds another `O(V)` complexity. Overall, the complexity is `O(V^2 + E)` which simplifies to `O(V^2)`.  

My algorithm is correct since it chooses a path based on the vertices that are closest to the origin. Only the shortest path to each vertex is recorded. Each node adjusts its distance when a neighboring node is checked and possesses a lower overall distance. Further, each vertex is only marked as visited when it is the unvisited vertex with the shortest overall distance from the origin in the graph. This allows its distance to be evaluated every time until it is no longer possible for a shorter path to that vertex to exist. Each vertex is marked as visited once, so all shortest paths are considered. Each vertex also keeps a pointer to the previous vertex in the path so the path can be displayed at the end. Lastly, all of this is performed in `O(V^2)` complexity without any kind of heap implementation.  

Problem 2
---------
My algorithm uses Dijkstra's algorithm in order to compute the single-source shortest path tree for a graph *G* rooted at a vertex *s*. This will create the single-source shortest path tree *SST(s)* rooted at *s*. Adding an edge with weight *w(u, v)* will ruin the tree since there will no longer be one less edge than vertice. Dijkstra's algorithm will need to be run again to regenerate the tree. However, it does not necessarily need to be run on the entire graph again. The algorithm will only be rerun on the lowest common ancestor of *u* and *v*. Dijkstra's will use the lowest common denominator of *u* and *v* as the source and all vertices in that subtree as the graph. To find the LCD I will have each vertice hold a property .visited that will initially be set to false. Starting at *u*, I will traverse up the tree setting the visited values to true until I reach *s*. Then, starting at *v*, I will traverse up the tree again. This time I will check if a vertice has been visited. I will add the unvisited vertices to a subgraph until I come across the first visited node. I will run Dijkstra's on this subgraph. The new *SST((LCD(u, v)))* will replace the existing subtree in *SST(s)*. *SST(s)* will be returned.  

```
newSST(G, SST, s, u, v):
    # I am assuming G is the graph with the new edge already added
    # G has a set of vertices V and a set of edges E
    # SST is the generated tree before the new edge was added
    # s is the source for the tree
    # u and v are the vertices that make up the new edge

    for each v in V:                        # initialize all vertices to unvisited
        v.visited = false

    current = u
    while current != s:                     # visit all ancestors of u
        u.visited = True
        current = current.parent
    s.visited = true                        # visit s

    current = v
    while current.visited != True:          # find LCD of u and v
        subgraph.insert(current)
        current = current.parent
    subgraph.insert(current)                # current is the LCD

    newSST = Dijkstra(subgraph, current)    # create new subtree
    SST.replaceSubtree(newSST)              # replace subtree from LCD

    return SST                              # return new tree with new edge
```  

The overall complexity of my algorithm is `O(ElogV)`. This is because initializing the values, visiting the ancestors of u, and finding the lowest common ancestor of *u* and *v* is `O(V)` since each vertice is visited at most once. Performing Dijkstra's takes `O(ElogV)` since it is performed on all of the vertices in the worst case. For the worst case, it appears no faster than simply running Dijkstra's algorithm again. However, the best and average case will be faster since it will not run the algorithm over the entire graph.  

My algorithm is correct because it is already commonly known that Dijkstra's algorithm can find the shortest path in a graph. My algorithm simply finds a subgraph of the original graph to run Dijkstra's on since it is unecessary to run it on the entire graph. Since adding an edge between *u* and *v* will only affect paths below the lowest common ancestor, a new path tree only needs to be generated for those vertices in this subtree..

Problem 3
---------  
My algorithm is based on the observation that adding one edge to a minimum spanning will always break the tree properties by creating a cycle. This is because a tree always has one less edge than vertices, so one edge must now be removed. In order to resolve the issue, my algorithm will first identify the vertices and the edges creating the cycle. It will compare the edge weights for the selected edges and remove the largest weight. To do this, I will use a stack to record the path, and each edge and vertice will hold an additional boolean for visited which is initially false. I will traverse the tree using a modified DFS. When each vertice is visited, it is added to the stack, and the visited values for it and the edge are set to true. If there are no unvisited adjacent paths to take, then the DFS will backtrack like normal to search for more paths. However, each backtracked vertice is popped off of the stack since they are not part of a cycle. If there is an adjacent vertice that has been visited but the path has not been taken, then a cycle has been identified. The path in the cycle is identified by popping the vertices from the stack until the original visited adjacent vertex is popped. The weights of the edges along this path are compared, and the largest one is removed from the tree. The new tree is returned.

```
newMCST(G, T, u, v):
    # I am assuming G is the graph with the new edge already added
    # G has a set of vertices V and a set of edges E
    # T is the generated tree with the new edge was added
    # u and v are the vertices that make up the new edge
    # path is an empty stack to record the path

    for v in V:
        v.visited = False

    for e in E:
        e.visited = False

    DFS(T)                          # traverses to add path for cycle

    start = path.top()              # first vertice in cycle
    source = NULL

    while True:
        source = path.top()
        path.pop()
        target = path.top()

        cycle.insert((source, target))      # cycle is array to hold cycle edges
        source = target

        if source == start:
            break

    maxEdge = cycle[0]
    for e in cycle:
        if e.weight > maxEdge.weight:
            maxEdge = e

    T.deleteEdge(maxEdge)

    return T

DFS(T, s):
    # tree t with root node s

    s.visited = True
    path.push(s)

    for e in s:                     # for all adjacent vertices to s
        if e.target.visted == False && e.visited == False:
            e.visited = True
            if DFS(T, e.target) == -1:
                return -1
        elif e.target.visited == True && e.visited == False:
            path.push(e.target)
            return -1               # cycle detected, break from function
```  

The overall complexity of my algorithm is `O(V + E)`. This is because initializing the graph is `O(V)` for the vertices and `O(E)` for the edges. DFS takes `O(V + E)` complexity since it visits at most each vertex and each edge. Finding the largest edge contained in the cycle also only takes `O(E)`, and deleting the edge is constant.  

My algorithm is correct because of the property that all trees have one less edge than vertices. Adding one edge to the tree means that one edge will need to be deleted since a cycle is inevitable. Only the edges in the cycle in the tree need to be considered since that paths to the other vertices will still be minimum. Since it is a minimum cost tree, removing the largest edge in the cycle resolves the issue. DFS properly visits each edge and vertex in the tree to identify the cycle. The stack `path` holds the path to the cycle by pushing vertices visited to it, and removing them again once the subtree is proven to not contain a cycle.  

Problem 4
---------  
My algorithm is based off of Prim's algorithm to find the minimum spanning tree. It will utilize a set *visited* that will contain all of the visited vertices. An adjacency matrix that is initially filled with zeros for the tree stores the tree. First, all edges with the weight zero will be removed from the graph since we are maximizing the product of the tree. Then, an arbitrary vertex will be added to *visited*. For each vertex in *visited*, all of the edges to unvisited, adjacent vertices will be compared. The edge with the largest weight will be added to *visited*, the total product will be multiplied by its weight, and the corresponding values in the adjacency matrix will be set to 1. These steps will be repeated for the tree until `|visited| = |V|`. If there are no unvisited vertices available and `|visited| != |V|`, then a tree is not possible without including zeros. Add the edges with weight zero back to the graph. Check again for unvisited adjacent vertices to complete the tree. If it is not possible, then return an error. Otherwise, return the tree.  

```
maxProductTree(G):
    # I am assuming G is the graph with V vertices and E edges

    for v1 in V:                                    # fill adj matrix with zeros
        for v2 in V:
            adjMatrix[v1][v2] = 0

    visited.insert(V[0])
    product = V[0]

    while |visited| != |V|:
        maxEdge = NULL

        for v in visited:                           # check all visited nodes
            for e in v.adjacent:                    # check edges for node

                if (e.target is not in visited &&   # ensure adj is unvisited
                    e.weight != 0:                  # ensure weight is not zero
                    if (maxEdge is NULL ||
                        e.weight > maxEdge):        # ensure edge is max
                        maxEdge = e

                elif e.target is not in visited:    # include zero weights
                    if (maxEdge is NULL ||
                        e.weight > maxEdge):        # ensure edge is max
                        maxEdge = e

                else:
                    return "No tree could be made."

        visited.insert(maxEdge.target)
        adjMatrix[maxEdge.source][maxEdge.target] = 1
        adjMatrix[maxEdge.target][maxEdge.source] = 1
        product *= maxEdge.weight

    print("A tree with weight " + product + " was found.")
    return adjMatrix
```  

The overall complexity of my algorithm is `O(V^2*E)`. This is because it takes `O(V^2)` to initialize the adjacency matrix. The while loop itself is `O(V)` complexity since it increases the visited nodes by one each time. Looping through the vertices and adjacent edges takes `O(V)` and `O(E)` respectively. Calculating the product and modifying the matrix each time is constant.  

My algorithm works because it consistently chooses the largest unvisited edge. In a similar way to how Prim's minimizes the tree, this will maximize the tree. Eliminating edges of weight zero also maximizes the product since an edge weight of zero would minimize the tree product to zero. However, these edges are included when it is impossible to construct a tree at all without them. By only visiting the unvisited nodes, it is guarunteed that there will be no cycles as well.