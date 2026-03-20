#include "Application.h"
#include "utils/DataLoader.h"
#include "utils/Timer.h"
#include "algorithms/NearestNeighbour.h"
#include "algorithms/RepetitiveNearestNeighbour.h"
#include "algorithms/RandomSearch.h"
#include "algorithms/BruteForce.h"
#include <iostream>
#include <cstdlib>

Application::Application() : isDataLoaded(false) {}

void Application::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Application::runAlgorithm(ITspAlgorithm* algorithm, const std::string& algorithmName) {
    if (!isDataLoaded) {
        std::cout << "You must load data from a file first." << std::endl;
        return;
    }

    std::cout << "\n--- Running: " << algorithmName << " ---" << std::endl;

    Timer timer;
    timer.start();

    TspResult* result = algorithm->solve(matrix);

    timer.stop();

    if (result != nullptr) {
        std::cout << "Path cost: " << result->cost << std::endl;
        std::cout << "Path: ";
        for (int i = 0; i < result->numVertices; ++i) {
            std::cout << result->path[i];
            if (i < result->numVertices - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
        std::cout << "Execution time: " << timer.getElapsedMicroseconds() << " us" << std::endl;

        delete result;
    }
    else {
        std::cout << "The algorithm did not return a result." << std::endl;
    }
}

void Application::loadData() {
    int formatChoice = 0;
    std::cout << "\n--- Select File Format ---" << std::endl;
    std::cout << "1. EXPLICIT (Full Matrix, e.g., atsp_5.txt)" << std::endl;
    std::cout << "2. EUC_2D (Coordinates, e.g., xqf131.txt)" << std::endl;
    std::cout << "Choose format: ";
    std::cin >> formatChoice;

    if (formatChoice != 1 && formatChoice != 2) {
        std::cout << "Invalid format selected. Returning to menu." << std::endl;
        return;
    }

    std::string filename;
    std::cout << "Enter the filename (e.g., data/atsp_5.txt): ";
    std::cin >> filename;

    bool success = false;

    if (formatChoice == 1) {
        success = DataLoader::loadFromFile(filename, matrix);
    }
    else if (formatChoice == 2) {
        success = DataLoader::loadCoordinatesFromFile(filename, matrix);
    }

    if (success) {
        isDataLoaded = true;
        std::cout << "Data loaded successfully!" << std::endl;
    }
    else {
        isDataLoaded = false;
        std::cout << "Failed to load data. Please check the file format and path." << std::endl;
    }
}

void Application::displayMatrix() {
    if (!isDataLoaded) {
        std::cout << "No data to display." << std::endl;
        return;
    }
    std::cout << "\n--- Cost Matrix ---" << std::endl;
    matrix.print();
}

void Application::run() {
    int choice = -1;

    clearScreen();

    while (choice != 0) {
        std::cout << "\n=======================================" << std::endl;
        std::cout << "   TRAVELING SALESMAN PROBLEM (TSP)    " << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "1. Load data from file" << std::endl;
        std::cout << "2. Display cost matrix" << std::endl;
        std::cout << "3. Brute-Force Algorithm" << std::endl;
        std::cout << "4. Nearest Neighbour (NN) Algorithm" << std::endl;
        std::cout << "5. Repetitive NN (RNN) Algorithm" << std::endl;
        std::cout << "6. Random Search Algorithm" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        clearScreen();

        switch (choice) {
        case 1:
            loadData();
            break;
        case 2:
            displayMatrix();
            break;
        case 3: {
            BruteForce bf;
            runAlgorithm(&bf, "Brute-Force");
            break;
        }
        case 4: {
            NearestNeighbour nn(0);
            runAlgorithm(&nn, "Nearest Neighbour");
            break;
        }
        case 5: {
            RepetitiveNearestNeighbour rnn;
            runAlgorithm(&rnn, "Repetitive Nearest Neighbour");
            break;
        }
        case 6: {
            int iterations;
            std::cout << "Enter the number of iterations for Random Search: ";
            std::cin >> iterations;
            clearScreen();
            RandomSearch randSearch(iterations);
            runAlgorithm(&randSearch, "Random Search");
            break;
        }
        case 0:
            std::cout << "Exiting the program..." << std::endl;
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
    }
}