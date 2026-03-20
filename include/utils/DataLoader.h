#pragma once
#include "core/TspMatrix.h"
#include <string>

class DataLoader {
    public:
		// Loads a TSP matrix from a file.
		// The file should be in a TSPLIB format with EDGE_WEIGHT_TYPE: EXPLICIT
        static bool loadFromFile(const std::string& filename, TspMatrix& matrix);

		// Loads coordinates from a file and fills the TSP matrix with the corresponding distances.
		// The file should contain coordinates in a TSPLIB format with EDGE_WEIGHT_TYPE: EUC_2D
		static bool loadCoordinatesFromFile(const std::string& filename, TspMatrix& matrix);
};