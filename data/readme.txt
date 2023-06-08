This three benchmark test sets are generated from CARP benchmarks.
Instances in Beijing (as well as Hefei) share the same undirected graph and vehical capacity but with different number of required edges and clusters.
Instances in EGL-G is divided into two types. Instances in each type share the same undirected graph and required edges but with different number of clusters and vehicle capacity. The difference between the two type is the required number of edges.
For each edge, the cost is set to the length of the road it represents and so dose its demand (if it is a required edge). 

An instance is characterized as follows:

1st line: the name of the instance;
2nd line: An additional comment on the data;
3rd line: Known optimal solution, or -1 if none;
4th line: the number of vertices;
5th line: Specifies the number of edges with positive demand (required edges);
6th line: Specifies the number of edges with zero demand (non required edges);
7th line: the number of clusters;
8th line: the number of vehicles;
9th line: the vehicle capacity;
10th line: Edge costs are listed explicitly in the corresponding section.
11th line: the total cost of required edges;
12th line: description of the next lines;

Next, there is a line for each edge in the graph, e.g. in file 'Beijing-1.txt',
the line corresponding to edge (2,3) is:
( 2, 3) coste 194 demanda 194
The 1st and 2nd number is the nodes number ("2" and "3");
The 3rd number is the cost of the edge;
The 4th number is the demand of the edge (Empty indicates it is a non-required edge)
Please note that each edge appears only once, but should be considered twice since it is an undirected graph.

Then, there is a line for each cluster, e.g. in file 'egl-g1-A.dat',
the line corresponding to the first cluster is:
#ARISTAS_EN_RACIMO : 1 ARISTAS : ( 128, 129) 
It means that this cluster has only one edge, which is (128,129)
