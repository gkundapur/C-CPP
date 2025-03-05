#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Node {
	int data;
	struct Node *next;
};
/*
    1------------3  
   /|            |
0 / |            |
  \ |            |
   \|            |
    2------------4
Initialially queue and visited arrays are empty
Visited = {}
Queue = {}
Front = 0

step 2: push 0 to queue and mark it visited
visited = {0}
Queue = {0}
Front = 0

step3: Remove 0 from front of queue and visit the unvisited neighbors
       and push them into queue
visited = {0, 1, 2}
queue = {1, 2}
Front = 0

step 4: Remove node 1 from the front of queue and visit unvisited neighbors
        and push them into queue
visited = {0, 1, 2, 3}
queue = {2, 3}
front = 0

step 5: Remove node 2 from the queue and visit unvisisted neighbors
visited = {0, 1, 2, 3, 4}
queue = {3, 4}

step6: Remove node 3 and visit the unvisited neighbors and push them
As we can see every neigbour of node 3 is visited, so move to next node
in the queue
visited = {0, 1, 2, 3, 4}
queue = {4}

step 7: Remove node 4 from the queue and visit unvisited neighbors
Every neighbours of node 4 is visisted, move to next node that is in queue
visited = {0, 1, 2, 3, 4}
queue = {}
queue is empty, terminate the iternation
*/

struct Node *
createNode(int data)
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;

	return node;
}

void
addEdge(struct Node *adj[], int u, int v)
{
	struct Node *node = createNode(v);
	node->next = adj[u];
	adj[u] = node;

	node = createNode(u);
	node->next = adj[v];
	adj[v] = node;
}

void
bfs(struct Node *adj[], int vertices, int source, int visited[])
{
	// create a queue for bfs
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	// mark the current node as visited
	visited[source] = 1;
	queue[rear++] = source;

	while (front != rear) {
		// dequeu a vertex from queue and print it
		int cur = queue[front++];
		printf("%d ", cur);

		// Get all adjacent vertices of dequeue vertex and mark it visited
		struct Node *temp = adj[cur];
		while (temp != NULL) {
			int neighbor = temp->data;
			if (!visited[neighbor]) {
				visited[neighbor] = 1;
				queue[rear++] = neighbor;
			}
			temp = temp->next;
		}
	}
}

int
main(void)
{
	int vertices = 5;

	struct Node *adj[vertices];

	for (int i = 0; i < vertices; i++)
		adj[i] = NULL;

	// add edges to graph
	addEdge(adj, 0, 1);
	addEdge(adj, 0, 2);
	addEdge(adj, 1, 3);
	addEdge(adj, 1, 4);
	addEdge(adj, 2, 4);

	int visited[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = 0;

	printf("BFS starting from vertex 0: ");
	bfs(adj, vertices, 0, visited);
	printf("\n");

	return 0;
}

