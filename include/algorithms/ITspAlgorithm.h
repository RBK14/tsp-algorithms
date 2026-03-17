#pragma once
#include "core/TspMatrix.h"

struct TspResult {
	int cost;			// Total cost of the TSP solution
	int* path;			// Array of vertex indices representing the path taken (including the return to the starting point)
	int numVertices;	// Number of vertices in the path (including the return to the starting point)

	TspResult(int vertices) {
		cost = 0;
		numVertices = vertices + 1;
		path = new int[numVertices];
	}

	~TspResult() {
		delete[] path;
	}

	// Block copy constructor and assignment operator to prevent copying
	TspResult(const TspResult&) = delete;
	TspResult& operator=(const TspResult&) = delete;
};

class ITspAlgorithm {
	public:
		virtual ~ITspAlgorithm() = default;

		virtual TspResult* solve(const TspMatrix& matrix) = 0;
};