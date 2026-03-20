#include "Application.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main() {
    srand(time(NULL));

    Application app;

	app.run();

    return 0;
}