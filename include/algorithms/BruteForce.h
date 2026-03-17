#pragma once
#include "ITspAlgorithm.h"

class BruteForce : public ITspAlgorithm {
    private:
		// Recursive function to evaluate all permutations of the vertices
        void evaluatePermutations(int currentNode, int step, int currentCost,
                                  int* currentPath, bool* visited,
                                  const TspMatrix& matrix, TspResult* bestResult);

    public:
        TspResult* solve(const TspMatrix& matrix) override;
};