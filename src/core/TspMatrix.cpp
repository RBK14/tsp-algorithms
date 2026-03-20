#include "core/TspMatrix.h"
#include <iostream>
#include <iomanip>

TspMatrix::TspMatrix() : matrix(nullptr), numVertices(0) { }

TspMatrix::~TspMatrix() {
    clear();
}

void TspMatrix::clear() {
    if (matrix != nullptr) {
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
    numVertices = 0;
}

bool TspMatrix::isValidVertex(int vertex) const {
    return vertex >= 0 && vertex < numVertices;
}

void TspMatrix::allocate(int size) {
    clear();

    numVertices = size;
    matrix = new int* [numVertices];

    for (int i = 0; i < numVertices; ++i) {
        matrix[i] = new int[numVertices];

        for (int j = 0; j < numVertices; ++j) {
            if (i == j) {
                matrix[i][j] = -1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
}

void TspMatrix::setWeight(int from, int to, int weight) {
    if (isValidVertex(from) && isValidVertex(to)) {
        matrix[from][to] = weight;
    }
}

int TspMatrix::getWeight(int from, int to) const {
    if (isValidVertex(from) && isValidVertex(to)) {
        return matrix[from][to];
    }
    return -1;
}

int TspMatrix::getNumVertices() const {
    return numVertices;
}

void TspMatrix::print() const {
    if (matrix == nullptr || numVertices == 0) {
        std::cout << "Empty weight matrix.\n";
        return;
    }

    std::cout << "Weight matrix (" << numVertices << "x" << numVertices << "):\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            std::cout << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}