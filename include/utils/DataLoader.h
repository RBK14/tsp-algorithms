#pragma once
#include "core/TspMatrix.h"
#include <string>

class DataLoader {
    public:
        static bool loadFromFile(const std::string& filename, TspMatrix& matrix);
};