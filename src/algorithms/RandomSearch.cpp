#include "algorithms/RandomSearch.h"
#include <climits>
#include <cstdlib>

RandomSearch::RandomSearch(int maxIterations) : iterations(maxIterations) { }

TspResult* RandomSearch::solve(const TspMatrix& matrix) {
	int n = matrix.getNumVertices();

	TspResult* bestResult = new TspResult(n);
	if (n == 0)
		return bestResult;

	bestResult->cost = INT_MAX;

	int* currentPath = new int[n];
	for (int i = 0; i < n; ++i) {
		currentPath[i] = i;
	}

    for (int iter = 0; iter < iterations; ++iter) {

        for (int i = n - 1; i > 0; --i) {
            int j = rand() % (i + 1);

            int temp = currentPath[i];
            currentPath[i] = currentPath[j];
            currentPath[j] = temp;
        }

        int currentCost = 0;
        bool isValidPath = true;

        for (int i = 0; i < n - 1; ++i) {
            int weight = matrix.getWeight(currentPath[i], currentPath[i + 1]);
            if (weight == -1) {
                isValidPath = false;
                break;
            }
            currentCost += weight;
        }

        if (isValidPath) {
            int returnWeight = matrix.getWeight(currentPath[n - 1], currentPath[0]);
            if (returnWeight == -1) {
                isValidPath = false;
            }
            else {
                currentCost += returnWeight;
            }
        }

        if (isValidPath && currentCost < bestResult->cost) {
            bestResult->cost = currentCost;
            for (int i = 0; i < n; ++i) {
                bestResult->path[i] = currentPath[i];
            }

            bestResult->path[n] = currentPath[0];
        }
    }

    delete[] currentPath;

    return bestResult;
}