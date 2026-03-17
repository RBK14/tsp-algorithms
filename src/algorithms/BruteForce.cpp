#include "algorithms/BruteForce.h"
#include <climits>

void BruteForce::evaluatePermutations(int currentNode, int step, int currentCost,
                                      int* currentPath, bool* visited,
                                      const TspMatrix& matrix, TspResult* bestResult) {
    int n = matrix.getNumVertices();

    if (step == n) {
		int returnCost = matrix.getWeight(currentNode, 0);

        if (returnCost != -1) {
			int totalCost = currentCost + returnCost;

            if (totalCost < bestResult->cost) {
                bestResult->cost = totalCost;
                for (int i = 0; i < n; ++i) {
                    bestResult->path[i] = currentPath[i];
                }

                bestResult->path[n] = 0;
            }
        }

        return;
    }

    for (int i = 1; i < n; ++i) {
        if (!visited[i]) {
            int edgeWeight = matrix.getWeight(currentNode, i);

            if (edgeWeight != -1) {
                visited[i] = true;
                currentPath[step] = i;

                evaluatePermutations(i, step + 1, currentCost + edgeWeight,
                                     currentPath, visited, matrix, bestResult);

                visited[i] = false;
            }
        }
    }
}

TspResult* BruteForce::solve(const TspMatrix& matrix) {
	int n = matrix.getNumVertices();

	TspResult* bestResult = new TspResult(n);
    if (n == 0)
		return bestResult;

    bestResult->cost = INT_MAX;

    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    int* currentPath = new int[n + 1];

    int startNode = 0;
    visited[startNode] = true;
    currentPath[0] = startNode;

    evaluatePermutations(startNode, 1, 0, currentPath, visited, matrix, bestResult);

    delete[] visited;
    delete[] currentPath;

    return bestResult;
}