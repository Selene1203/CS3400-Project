#include "objects/system.h"

int main() {
    // Create system pointed at the data directory, load state, run CLI, then save on exit
    System sys("data");
    sys.loadAll();
    sys.runCLI();
    sys.saveAll();
    return 0;
}
