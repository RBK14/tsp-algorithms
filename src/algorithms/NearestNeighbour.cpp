#include "algorithms/NearestNeighbour.h"
#include <climits>

NearestNeighbour::NearestNeighbour(int startNode) : startNode(startNode) {}

TspResult* NearestNeighbour::solve(const TspMatrix& matrix) {
	int n = matrix.getNumVertices();

	TspResult* result = new TspResult(n);

	if (n == 0)
		return result;

	bool* visited = new bool[n];
	for (int i = 0; i < n; ++i) {
		visited[i] = false;
	}

	int currentNode = startNode;
	visited[currentNode] = true;
	result->path[0] = currentNode;
	result->cost = 0;

	for (int step = 1; step < n; ++step) {
		int minCost = INT_MAX;
		int nextNode = -1;

		for (int candidate = 0; candidate < n; ++candidate) {
			if (!visited[candidate]) {
				int cost = matrix.getWeight(currentNode, candidate);
				if (cost != -1 && cost < minCost) {
					minCost = cost;
					nextNode = candidate;
				}
			}
		}

		currentNode = nextNode;
		visited[currentNode] = true;
		result->path[step] = currentNode;
		result->cost += minCost;
	}

	result->cost += matrix.getWeight(currentNode, startNode);
	result->path[n] = startNode;

	delete[] visited;

	return result;
}