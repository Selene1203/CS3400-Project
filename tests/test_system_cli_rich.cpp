#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include "objects/system.h"

int main() {
    namespace fs = std::filesystem;
    const std::string dir = "data_cli_rich";
    try { fs::create_directory(dir); } catch(...) {}

    const std::string inputPath = dir + "/cli_input.txt";
    std::ofstream in(inputPath);
    if (!in) {
        std::cerr << "Failed to create input file" << std::endl;
        return 2;
    }

    // Steps:
    // 1) Register patient
    // 2) Add triage case for that patient
    // 3) View patient logs
    // 4) Save and exit

    // Register
    in << "1\n";
    in << "Alice\n"; // first
    in << "Smith\n"; // last
    in << "F\n"; // gender
    in << "1985-05-05\n"; // dob
    in << "555-1234\n"; // phone
    in << "42 Example Road\n"; // address
    in << "424242\n"; // national id

    // Add triage case (choice 2)
    in << "2\n";
    in << "1\n"; // patient id
    in << "2\n"; // triage level
    in << "Severe abdominal pain\n"; // condition (multi-word)
    in << "2025-10-26T12:00\n"; // time reported

    // View logs (choice 6)
    in << "6\n";
    in << "1\n"; // patient id

    // Save and exit
    in << "7\n";
    in.close();

    FILE* f = freopen(inputPath.c_str(), "r", stdin);
    if (!f) { std::cerr << "Failed to redirect stdin" << std::endl; return 2; }

    System sys(dir);
    sys.loadAll();
    sys.runCLI();
    sys.saveAll();

    // Verify logs were added
    auto logs = sys.getPatientLogs(1);
    if (logs.empty()) {
        std::cerr << "Rich CLI test failed: no logs found" << std::endl;
        return 1;
    }
    std::cout << "Rich CLI test passed (" << logs.size() << " logs)" << std::endl;
    return 0;
}
