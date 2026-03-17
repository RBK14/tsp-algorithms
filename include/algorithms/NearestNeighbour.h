#pragma once
#include "ITspAlgorithm.h"

class NearestNeighbour : public ITspAlgorithm {
	private:
		int startNode;

	public:
		NearestNeighbour(int startNode = 0);

		TspResult* solve(const TspMatrix& matrix) override;
};