#include "main.h"
// #define MAX_LINE_LENGTH 64


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
            genAllPosMov(false);
        }else if(equals(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")){
			genAllPosMov(true);
		}
    }

    return 0;
}
