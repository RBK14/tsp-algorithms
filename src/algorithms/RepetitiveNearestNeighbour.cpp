#include "algorithms/RepetitiveNearestNeighbour.h"
#include <climits>

TspResult* RepetitiveNearestNeighbour::solve(const TspMatrix& matrix) {
	int n = matrix.getNumVertices();

	TspResult* bestResult = nullptr;
	if (n == 0)
		return bestResult;

	bestresult->cost = INT_MAX;

	bool* visited = new bool[n];
	int* currentPath = new int[n + 1];

	for (int startNode = 0; startNode < n; ++startNode) {
		for (int i = 0; i < n; ++i) {
			visited[i] = false;
		}

		int currentNode = startNode;
		visited[currentNode] = true;
		currentPath[0] = currentNode;
		int currentCost = 0;

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
			currentPath[step] = currentNode;
			currentCost += minCost;
		}

		currentCost += matrix.getWeight(currentNode, startNode);
		currentPath[n] = startNode;

		if (currentCost < bestResult->cost) {
			bestResult->cost = currentCost;
			for (int i = 0; i < n + 1; ++i) {
				bestResult->path[i] = currentPath[i];
			}
		}
	}

	delete[] visited;
	delete[] currentPath;

	return bestResult;
}