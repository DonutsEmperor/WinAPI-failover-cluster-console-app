#pragma once

#include <windows.h>
#include <iostream>
#include "ClusApi.h"

#include "headers/Cluster.h"

#pragma comment(lib, "ClusAPI.lib")

enum ErrorCode {
    NoError = 0,
    FileNotFound,
    InvalidInput
};

ErrorCode performOperation() {
    // Simulating an error
    return FileNotFound;
}

int main() {
    ErrorCode result = performOperation();

    if (result == FileNotFound) {
        std::cout << "File not found!" << std::endl;
    }
    else if (result == InvalidInput) {
        std::cout << "Invalid input!" << std::endl;
    }
    else {
        std::cout << "Operation successful!" << std::endl;
    }

    return 0;
}