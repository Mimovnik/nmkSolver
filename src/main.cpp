#include "main.h"

#include <iostream>
#include <string>

#include "Commands.h"

bool equals(const char* str1, const char* str2) {
	for (int i = 0; i < MAX_LINE_LENGTH; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
		else if (str1[i] == '\0' || str2[i] == '\0') {
			return true;
		}
	}
	return true;
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
