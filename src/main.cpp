#include <iostream>

#include "Commands.h"

int main() {
    char command[MAX_LINE_LENGTH];

    while (std::cin >> command) {
        if (equals(command, "GEN_ALL_POS_MOV")) {
            genAllPosMov();
        }
    }

    return 0;
}
