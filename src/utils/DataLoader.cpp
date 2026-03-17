#include "io/DataLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool DataLoader::loadFromFile(const std::string& filename, TspMatrix& matrix) {
	std::ifstream file(filename);

	if (!file.is_open) {
		std::cerr << "An error occurred while opening teh file: " << filename << std::endl;
		return false;
	}

	std::string line;
	int dimension = 0;
	bool readingMatrix = false;

	// Parse the file to find the dimension and the start of the edge weight section
    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (line.find("DIMENSION") != std::string::npos) {
            std::size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                dimension = std::stoi(line.substr(colonPos + 1));
            }
        }
        else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            inWeightSection = true;
            break;
        }
    }

    if (!inWeightSection || dimension <= 0) {
        std::cerr << "Invalid file forma (DIMENSION lub EDGE_WEIGHT_SECTION is missing)." << std::endl;
        return false;
    }

    matrix.allocate(dimension);

    int count = 0;
    int totalElements = dimension * dimension;

	// Read the edge weight section and fill the matrix
    while (count < totalElements && std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (ss >> token && count < totalElements) {
            if (token == "EOF") break;

            try {
                int weight = std::stoi(token);

                int row = count / dimension;
                int col = count % dimension;

				// Set the weight in the matrix, ensuring that diagonal elements are set to -1
                if (row == col) {
                    matrix.setWeight(row, col, -1);
                }
                else {
                    matrix.setWeight(row, col, weight);
                }

                count++;
            }
            catch (const std::invalid_argument&) {
                continue;
            }
            catch (const std::out_of_range&) {
                continue;
            }
        }

		file.close();

        if (count < totalElements) {
            std::cerr << "Invalid weight matrix for dimension " << dimension << "." << std::endl;
            return false;
        }

		return true;
    }
}