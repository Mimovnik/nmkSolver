#include "main.h"

#include <iostream>
#include <string.h>

#include "Commands.h"

bool equals(const char* str1, const char* str2) {
	if(strcmp(str1, str2) == 0){
		return true;
	}
	return false;
}

int MYmain() {
    char* command = new char[MAX_LINE_LENGTH];

    while (std::cin >> command) {
        if (equals(command, "GEN_ALL_POS_MOV")) {
            genAllPosMov();
        }
    }

    return 0;
}
