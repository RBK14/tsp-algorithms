#include "utils/DataLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

bool DataLoader::loadFromFile(const std::string& filename, TspMatrix& matrix) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "An error occurred while opening the file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int dimension = 0;
    bool inWeightSection = false;

    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (line.find("DIMENSION") != std::string::npos) {
            std::string numStr = "";
            for (char c : line) {
                if (std::isdigit(c)) numStr += c;
            }
            if (!numStr.empty()) dimension = std::stoi(numStr);
        }
        else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
            inWeightSection = true;
            break;
        }
    }

    if (!inWeightSection || dimension <= 0) {
        std::cerr << "Invalid file format for explicit matrix." << std::endl;
        return false;
    }

    matrix.allocate(dimension);
    int count = 0;
    int totalElements = dimension * dimension;

    while (count < totalElements && std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (ss >> token && count < totalElements) {
            if (token == "EOF") break;

            try {
                int weight = std::stoi(token);
                int row = count / dimension;
                int col = count % dimension;

                if (row == col) {
                    matrix.setWeight(row, col, -1);
                }
                else {
                    matrix.setWeight(row, col, weight);
                }
                count++;
            }
            catch (...) {
                continue;
            }
        }
    }

    file.close();

    if (count < totalElements) return false;
    return true;
}

bool DataLoader::loadCoordinatesFromFile(const std::string& filename, TspMatrix& matrix) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "An error occurred while opening the file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int dimension = 0;
    bool inCoordSection = false;

    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (line.find("DIMENSION") != std::string::npos) {
            std::string numStr = "";
            for (char c : line) {
                if (std::isdigit(c)) numStr += c;
            }
            if (!numStr.empty()) dimension = std::stoi(numStr);
        }
        else if (line.find("NODE_COORD_SECTION") != std::string::npos) {
            inCoordSection = true;
            break;
        }
    }

    if (!inCoordSection || dimension <= 0) {
        std::cerr << "Invalid file format for coordinates (EUC_2D)." << std::endl;
        return false;
    }

    std::vector<std::pair<double, double>> coords(dimension);
    int readNodes = 0;

    while (readNodes < dimension && std::getline(file, line)) {
        if (line.find("EOF") != std::string::npos) break;

        std::stringstream ss(line);
        int id;
        double x, y;

        if (ss >> id >> x >> y) {
            if (id > 0 && id <= dimension) {
                coords[id - 1] = { x, y };
                readNodes++;
            }
        }
    }

    if (readNodes < dimension) {
        std::cerr << "Not enough coordinates found in file." << std::endl;
        return false;
    }

    matrix.allocate(dimension);

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (i == j) {
                matrix.setWeight(i, j, -1);
            }
            else {
                double dx = coords[i].first - coords[j].first;
                double dy = coords[i].second - coords[j].second;
                int distance = static_cast<int>(std::round(std::sqrt(dx * dx + dy * dy)));
                matrix.setWeight(i, j, distance);
            }
        }
    }

    file.close();
    return true;
}