#pragma once
#include "ITspAlgorithm.h"

class RandomSearch : public ITspAlgorithm {
    private:
	    int iterations; // Number of random solutions to generate

    public:
        RandomSearch(int maxIterations = 100000);

        TspResult* solve(const TspMatrix& matrix) override;
};