#pragma once
#include "core/TspMatrix.h"
#include "algorithms/ITspAlgorithm.h"
#include <string>

class Application {
    private:
        TspMatrix matrix;
        bool isDataLoaded;

        void runAlgorithm(ITspAlgorithm* algorithm, const std::string& algorithmName);

		void clearScreen();
        void loadData();
        void displayMatrix();

    public:
        Application();

        void run();
};