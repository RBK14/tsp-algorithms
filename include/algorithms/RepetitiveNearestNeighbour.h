#pragma once
#include "ITspAlgorithm.h"

class RepetitiveNearestNeighbour : public ITspAlgorithm {
    public:
        TspResult* solve(const TspMatrix& matrix) override;
};