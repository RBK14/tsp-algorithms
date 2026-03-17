#pragma once
#include "ITspAlgorithm.h"

class RepetitiveNn : public ITspAlgorithm {
    public:
        TspResult* solve(const TspMatrix& matrix) override;
};