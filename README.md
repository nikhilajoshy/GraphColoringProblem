# GraphColoringProblem
Four algorithms are implemented in this experiment.
First is to use the greedy approach to find the number
of colors required to color the vertices of the
graph such that no two adjacent vertices will have
same color. Second and third algorithm is using the
approximation method to solve the vertex coloring
problem with an approximation of Δ +1 where Δ
is the maximum degree of the graph. In addition
to these, the last algorithm is exact minimum vertex
color computation using a bounded search tree.
In the experiments, it is concluded that the simple
greedy approach returns the number of colors required
to color the graph with maximum number of
colors whereas using the approximation algorithm,
gives better results with a Δ +1 guarantee. When implementing
the approximation algorithm while taking
the degree of the vertices into consideration, it
results in a slightly lesser number of colors for some
graphs. The exact algorithm employs a parametrized
approach to identify if the adjacent vertices of the
graph can be uniquely colored with the given value.
