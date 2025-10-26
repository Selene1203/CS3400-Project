#include <iostream>
#include "objects/system.h"

int main() {
    System sys("data");
    bool loaded = sys.loadAll();
    std::cout << "System: loadAll returned " << (loaded ? "true" : "false") << std::endl;
    bool saved = sys.saveAll();
    std::cout << "System: saveAll returned " << (saved ? "true" : "false") << std::endl;
    return (loaded && saved) ? 0 : 1;
}
