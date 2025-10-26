#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include "objects/system.h"

int main() {
    namespace fs = std::filesystem;
    const std::string dir = "data_cli_test";
    // ensure test data directory exists
    try { fs::create_directory(dir); } catch(...) {}

    const std::string inputPath = dir + "/cli_input.txt";
    // Prepare simulated user input: register a patient then save & exit (choice 7)
    std::ofstream in(inputPath);
    if (!in) {
        std::cerr << "Failed to create input file" << std::endl;
        return 2;
    }
    // runCLI now expects line-based prompts. Provide each field on its own line.
    in << "1\n"; // choice: register
    in << "John\n"; // First name
    in << "Doe\n"; // Last name
    in << "M\n"; // Gender
    in << "1990-01-01\n"; // DOB
    in << "555-0000\n"; // Phone
    in << "123 Main Street Apt 4\n"; // Address (contains spaces)
    in << "99999\n"; // National ID
    in << "7\n"; // choice: save and exit
    in.close();

    // Redirect stdin to our input file
    FILE* f = freopen(inputPath.c_str(), "r", stdin);
    if (!f) {
        std::cerr << "Failed to redirect stdin" << std::endl;
        return 2;
    }

    System sys(dir);
    sys.loadAll();
    sys.runCLI();
    sys.saveAll();

    // After running the CLI, the registered patient should exist with id 1
    Patient* p = sys.findPatient(1);
    if (!p) {
        std::cerr << "CLI test failed: patient not found" << std::endl;
        return 1;
    }

    std::cout << "CLI test passed" << std::endl;
    return 0;
}
